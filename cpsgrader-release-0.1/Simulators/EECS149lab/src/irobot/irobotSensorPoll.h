/** \file irobotSensorPoll.h
 *
 * Methods to poll iRobot sensors.
 *
 * \author Jeff C. Jensen
 * \date 2013-12-09
 * \copyright Copyright (C) 2013, Jeff C. Jensen, Edward A. Lee, and Sanjit A. Seshia.
 * 			  This software accompanies An Introductory Lab in Embedded and Cyber-Physical Systems
 * 			  and is licensed under a Creative Commons Attribution-NonCommercial-NoDerivs 3.0
 * 			  Unported License. See http://leeseshia.org/lab.
 */

#ifndef _IROBOT_SENSORPOLL_H
#define _IROBOT_SENSORPOLL_H

#include "irobotUART.h"
#include "irobotSensorTypes.h"

/// Request sensor packet from iRobot and wait for response
/// \warning Polling requires both transmitting and receiving
///				to the UART port, hence these functions are *not*
///				thread safe with regard to other UART functions.
/// \return error code
int32_t irobotSensorPollSensorGroup6(
	const irobotUARTPort_t			port,				///< [in] iRobot UART port
	irobotSensorGroup6_t * const	sensorGroup6		///< [in] Sensor group
);

#endif // _IROBOT_SENSORPOLL_H
