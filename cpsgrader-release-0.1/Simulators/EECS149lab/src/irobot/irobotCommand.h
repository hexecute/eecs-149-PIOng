/** \file irobotCommand.h
 *
 * iRobot general commands.
 *
 * \author Jeff C. Jensen
 * \date 2013-12-09
 * \copyright Copyright (C) 2013, Jeff C. Jensen, Edward A. Lee, and Sanjit A. Seshia.
 * 			  This software accompanies An Introductory Lab in Embedded and Cyber-Physical Systems
 * 			  and is licensed under a Creative Commons Attribution-NonCommercial-NoDerivs 3.0
 * 			  Unported License. See http://leeseshia.org/lab.
 */

#ifndef _IROBOTCOMMAND_H
#define _IROBOTCOMMAND_H

#include "irobotOpcode.h"
#include "irobotUART.h"
#include "irobotError.h"

/// Demo modes
typedef enum{
	DEMO_COVER				= 0,	///< Cover demo
	DEMO_COVER_DOCK			= 1,	///< Cover & dock demo
	DEMO_SPOT_COVER			= 2,	///< Spot cover demo
	DEMO_MOUSE				= 3,	///< Mouse demo
	DEMO_DRIVE_FIGURE_EIGHT	= 4,	///< Figure eight demo
	DEMO_WIMP				= 5,	///< Wimp demo
	DEMO_HOME				= 6,	///< Home demo
	DEMO_TAG				= 7,	///< Tag demo
	DEMO_PACHELBEL			= 8,	///< Pachelbel song demo
	DEMO_BANJO				= 9		///< Banjo song demo
} irobotDemo_t;

/// Set the iRobot baud rate. The serial port will be reconfigured to this new
/// baud rate and restarted, which will clear communication buffers and may introduce a delay.
/// \warning baud 115200 appears to be unstable.
/// \return error code
int32_t irobotBaudChange(
	const irobotUARTPort_t	port,		///< [in] UART port
	const irobotBaud_t		baud		///< [in] iRobot baud code
);

/// Stop a running demo
int32_t irobotDemoStop(
	const irobotUARTPort_t	port		///< [in] UART port
);

/// Run a demo
int32_t irobotDemo(
	const irobotUARTPort_t	port,		///< [in] UART port
	const irobotDemo_t		demo		///< [in] demo to run
);

/// Change to FULL mode
int32_t irobotFull(
	const irobotUARTPort_t	port		///< [in] UART port
);

/// Change to SAFE mode
int32_t irobotSafe(
	const irobotUARTPort_t	port		///< [in] UART port
);

/// Change to START mode
int32_t irobotStart(
	const irobotUARTPort_t	port		///< [in] UART port
);


#endif // _IROBOTCOMMAND_H
