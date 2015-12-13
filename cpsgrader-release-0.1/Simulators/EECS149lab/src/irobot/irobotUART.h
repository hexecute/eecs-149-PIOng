/** \file irobotUART.h
 *
 * UART wrappers for the iRobot Create. This library is not architecture
				specific, so these are only wrappers for UART functions that must
				be defined for your architecture.
 *
 * \author Jeff C. Jensen
 * \date 2013-12-09
 * \copyright Copyright (C) 2013, Jeff C. Jensen, Edward A. Lee, and Sanjit A. Seshia.
 * 			  This software accompanies An Introductory Lab in Embedded and Cyber-Physical Systems
 * 			  and is licensed under a Creative Commons Attribution-NonCommercial-NoDerivs 3.0
 * 			  Unported License. See http://leeseshia.org/lab.
 */

#ifndef _IROBOT_UART_H
#define _IROBOT_UART_H

#include "irobotTypes.h"
#include "irobotError.h"
#include "xqueue.h"
#include "UART.h"

/// UART port wrapper; change for your UART API
typedef MyRio_Uart * irobotUARTPort_t;

extern irobotUARTPort_t UART1;		///< UART port 1; defined in irobotUART.c
extern irobotUARTPort_t UART2;		///< UART port 2; defined in irobotUART.c

/// Baud rate codes
typedef enum{
	IROBOT_BAUD_300		= 0,	///< UART baud rate 300bps
	IROBOT_BAUD_600		= 1,	///< UART baud rate 600bps
	IROBOT_BAUD_1200	= 2,	///< UART baud rate 1200bps
	IROBOT_BAUD_2400	= 3,	///< UART baud rate 2400bps
	IROBOT_BAUD_4800	= 4,	///< UART baud rate 4800bps
	IROBOT_BAUD_9600	= 5,	///< UART baud rate 9600bps
	IROBOT_BAUD_14400	= 6,	///< UART baud rate 14400bps
	IROBOT_BAUD_19200	= 7,	///< UART baud rate 19200bps
	IROBOT_BAUD_28800	= 8,	///< UART baud rate 28800bps
	IROBOT_BAUD_38400	= 9,	///< UART baud rate 38400bps
	IROBOT_BAUD_57600	= 10,	///< UART baud rate 57600bps
	IROBOT_BAUD_115200	= 11	///< UART baud rate 115200bps	\warning UNSTABLE
} irobotBaud_t;

/// Opens a UART session configured for the iRobot
/// \return error code
int32_t irobotUARTOpen(
	const irobotUARTPort_t	port,		///< [in] UART port
	const irobotBaud_t		baud		///< [in] baud rate of the port
);

/// Closes the UART port connected to iRobot. The port must be reinitialized before reuse.
/// \return error code
int32_t irobotUARTClose(
	const irobotUARTPort_t	port		///< [in] UART port
);

/// Read data from the UART receive buffer until # have been
/// received, or until a timeout occurs. A negative timeout means wait indefinitely.
/// Read bytes are pushed to the queue; if the queue is full, its oldest bytes are dropped.
/// \return error code
int32_t irobotUARTRead(
	const irobotUARTPort_t	port,		///< [in] UART port
	xqueue_t * const		queue,		///< [out]Queue to receive read data
	size_t					nData		///< [in] Number of bytes to read
);

/// Read data from the UART receive buffer until # have been
/// received, or until a timeout occurs. A negative timeout means wait indefinitely.
/// \return error code
int32_t irobotUARTReadRaw(
	const irobotUARTPort_t	port,		///< [in] UART port
	uint8_t * const			data,		///< [out]Buffer to receive read data
	const size_t			nData		///< [in] Number of bytes to read
);

/// Writes a queue to the UART port. If not enough space is available in the FIFO,
/// this function blocks until sufficient space is available or a timeout occurs.
/// Elements written are popped from the queue.
/// \return error code
int32_t irobotUARTWrite(
	const irobotUARTPort_t	port,		///< [in] UART port to access
	xqueue_t * const		queue		///< [in] Queue data to write; all will be written
);

/// Writes data to the UART port. If not enough space is available in the FIFO,
/// this function blocks until sufficient space is available or a timeout occurs.
/// \return error code
int32_t irobotUARTWriteRaw(
	const irobotUARTPort_t	port,		///< [in] UART port to access
	const uint8_t * const	data,		///< [in] Array of data to write
	const size_t			nData		///< [in] Size of data array
);

/// Clears the UART receive buffer.
/// \return error code
int32_t irobotUARTClear(
	const irobotUARTPort_t	port		///< [in] UART port to access
);

#endif	// _IROBOT_UART_H
