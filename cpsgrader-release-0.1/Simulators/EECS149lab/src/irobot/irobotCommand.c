#include "irobotCommand.h"
#include "irobotTime.h"

int32_t irobotBaudChange(
	const irobotUARTPort_t	port,
	const irobotBaud_t		baud
){
	int32_t status = ERROR_SUCCESS;
	uint8_t packet[OP_BAUD_SIZE];

	packet[0] = OP_BAUD;
	packet[1] = (uint8_t)baud;
	
	if(!irobot_IsError(status)){
		irobot_StatusMerge(&status, irobotUARTWriteRaw(port, packet, OP_BAUD_SIZE));
	}
	if(!irobot_IsError(status)){
		irobot_StatusMerge(&status, irobotUARTClose(port));
	}
	if(!irobot_IsError(status)){
		irobot_StatusMerge(&status, irobotUARTOpen(port, baud));
		irobotDelayMs(50); // delay 50ms
	}

	return status;
}

int32_t irobotDemoStop(
	const irobotUARTPort_t	port
){
	uint8_t packet[OP_DEMO_SIZE];

	packet[0] = OP_DEMO;
	packet[1] = 0xFF;		/* special case; stop all demos */
	
	return irobotUARTWriteRaw(port, packet, OP_DEMO_SIZE);
}

int32_t irobotDemo(
	const irobotUARTPort_t	port,
	const irobotDemo_t		demo
){
	uint8_t packet[OP_DEMO_SIZE];

	packet[0] = OP_DEMO;
	packet[1] = (uint8_t)demo;
	
	return irobotUARTWriteRaw(port, packet, OP_DEMO_SIZE);
}

int32_t irobotFull(
	const irobotUARTPort_t	port
){
	uint8_t packet[OP_FULL_SIZE];

	packet[0] = OP_FULL;
	
	return irobotUARTWriteRaw(port, packet, OP_FULL_SIZE);
}

int32_t irobotSafe(
	const irobotUARTPort_t	port
){
	uint8_t packet[OP_SAFE_SIZE];

	packet[0] = OP_SAFE;
	
	return irobotUARTWriteRaw(port, packet, OP_SAFE_SIZE);
}

int32_t irobotStart(
	const irobotUARTPort_t	port
){
	uint8_t packet[OP_START_SIZE];

	packet[0] = OP_START;
	
	return irobotUARTWriteRaw(port, packet, OP_START_SIZE);
}

