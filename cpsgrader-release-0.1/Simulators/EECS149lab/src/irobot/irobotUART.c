#include "irobotUART.h"

static MyRio_Uart _UART1 = {"ASRL1::INSTR", 0, 0};	///< Global reference to UART1 port
static MyRio_Uart _UART2 = {"ASRL2::INSTR", 0, 0};	///< Global reference to UART2 port

// Assign iRobot UART ports to the global references
irobotUARTPort_t UART1 = &_UART1;
irobotUARTPort_t UART2 = &_UART2;

/// Convert a baud code into its actual rate
/// \return error code
static int32_t irobotUARTBaudCodeToRate(
	const irobotBaud_t	baud,		///< [in]	baud code
	uint32_t * const	rate		///< [out]	baud rate
){
	if(!rate){
		return ERROR_INVALID_PARAMETER;
	}
	else{
		switch(baud){
		case IROBOT_BAUD_300:	*rate = 300;	break;
		case IROBOT_BAUD_600:	*rate = 600;	break;
		case IROBOT_BAUD_1200:	*rate = 1200;	break;
		case IROBOT_BAUD_2400:	*rate = 2400;	break;
		case IROBOT_BAUD_4800:	*rate = 4800;	break;
		case IROBOT_BAUD_9600:	*rate = 9600;	break;
		case IROBOT_BAUD_14400:	*rate = 14400;	break;
		case IROBOT_BAUD_19200:	*rate = 19200;	break;
		case IROBOT_BAUD_28800:	*rate = 28800;	break;
		case IROBOT_BAUD_38400:	*rate = 38400;	break;
		case IROBOT_BAUD_57600:	*rate = 57600;	break;
		case IROBOT_BAUD_115200:*rate = 115200;	break;	// WARNING: UNSTABLE
		default:
			*rate = 0;
			return ERROR_INVALID_PARAMETER;
			break;
		}

		return ERROR_SUCCESS;
	}
}

int32_t irobotUARTOpen(
	const irobotUARTPort_t	port,
	const irobotBaud_t		baud
){
	int32_t status = ERROR_SUCCESS;
	uint32_t baudRate = 0;
	
	irobot_StatusMerge(&status, irobotUARTBaudCodeToRate(baud, &baudRate));

	if(!irobot_IsError(status)){
		irobot_StatusMerge(
			&status,
			Uart_Open(
				port,
				baudRate,
				8,
				Uart_StopBits1_0,
				Uart_ParityNone
			)
		);
	}

	return status;
}

int32_t irobotUARTClose(
	const irobotUARTPort_t	port
){
	return Uart_Close(port);
}

int32_t irobotUARTRead(
	const irobotUARTPort_t	port,
	xqueue_t * const		queue,
	size_t					nData
){
	int32_t status = ERROR_SUCCESS;

	// catch NULL pointers
	if(!queue){
		irobot_StatusMerge(&status, ERROR_INVALID_PARAMETER);
	}
	
	// read
	while(!irobot_IsError(status) && nData--){
		uint8_t rxByte = 0;
		irobot_StatusMerge(&status, irobotUARTReadRaw(port, &rxByte, 1));
		if(!irobot_IsError(status)){
			xqueue_push8(queue, rxByte);
		}
		if(status == 1073676294){
			status = 0;	// ignore VISA "num bytes req = num bytes read"
		}
	}

	return status;
}

int32_t irobotUARTReadRaw(
	const irobotUARTPort_t	port,
	uint8_t * const			data,
	const size_t			nData
){
	// catch NULL pointers
	if(!data){
		return ERROR_INVALID_PARAMETER;
	}
	else{
		return Uart_Read(port, data, nData);
	}
}

int32_t irobotUARTWrite(
	const irobotUARTPort_t	port,
	xqueue_t * const		queue
){
	int32_t status = ERROR_SUCCESS;

	// catch NULL pointers
	if(!queue){
		irobot_StatusMerge(&status, ERROR_INVALID_PARAMETER);
	}
	
	// write
	while(!irobot_IsError(status) && !xqueue_empty(queue)){
		uint8_t txByte = xqueue_front(queue);
		irobot_StatusMerge(&status, irobotUARTWriteRaw(port, &txByte, 1));
		if(!irobot_IsError(status)){
			xqueue_drop(queue);
		}
	}

	return status;
}

int32_t irobotUARTWriteRaw(
	const irobotUARTPort_t	port,
	const uint8_t * const	data,
	const size_t			nData
){
	// catch NULL pointers
	if(!data){
		return ERROR_INVALID_PARAMETER;
	}
	else{
		return Uart_Write(port, data, nData);
	}
}

int32_t irobotUARTClear(
	const irobotUARTPort_t	port
){
	return Uart_Clear(port);
}

