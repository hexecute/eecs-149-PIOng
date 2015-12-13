/** \file irobot.h
 *
 * Top-level driver for the iRobot Create.
 * Implements irobotOpen() and irobotClose()
 *
 * \author Jeff C. Jensen
 * \date 2013-10-17
 * \copyright Copyright (C) 2013, Jeff C. Jensen, Edward A. Lee, and Sanjit A. Seshia.
 * 			  This software accompanies An Introductory Lab in Embedded and Cyber-Physical Systems
 * 			  and is licensed under a Creative Commons Attribution-NonCommercial-NoDerivs 3.0
 * 			  Unported License. See http://leeseshia.org/lab.
 */

#ifndef _IROBOT_H
#define _IROBOT_H

#include "irobotUART.h"
#include "irobotSensor.h"
#include "irobotSensorPoll.h"
#include "irobotSensorStream.h"
#include "irobotActuator.h"
#include "irobotCommand.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/// Open UART serial port and initialize iRobot.
/// \return error code
int32_t irobotOpen(
	const irobotUARTPort_t	port		///< [in] UART port
);

/// Close a session with an iRobot
/// \return error code
int32_t irobotClose(
	const irobotUARTPort_t	port		///< [in] UART port
);


#endif	// _IROBOT_H
