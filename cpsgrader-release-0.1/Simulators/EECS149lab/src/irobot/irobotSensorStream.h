/** \file irobotSensorStream.h
 *
 * iRobot sensor stream functions
 *
 * \author Jeff C. Jensen
 * \date 2013-12-09
 * \copyright Copyright (C) 2013, Jeff C. Jensen, Edward A. Lee, and Sanjit A. Seshia.
 * 			  This software accompanies An Introductory Lab in Embedded and Cyber-Physical Systems
 * 			  and is licensed under a Creative Commons Attribution-NonCommercial-NoDerivs 3.0
 * 			  Unported License. See http://leeseshia.org/lab.
 */

#ifndef _IROBOTSTREAM_H
#define _IROBOTSTREAM_H

#include "irobotUART.h"
#include "irobotSensorTypes.h"

/// configure a sensors stream
/// \return error code
int32_t irobotSensorStreamConfigure(
	const irobotUARTPort_t			port,			///< [in] irobot UART port
	const irobotSensorCode * const	sensorCodes,	///< [in] array of sensor codes (must be nSensorCodes in size)
	uint8_t							nSensorCodes	///< [in] number of sensors in each stream packet
);

/// pause or resume a sensor stream
/// \return error code
int32_t irobotSensorStreamPause(
	const irobotUARTPort_t port,					///< [in] irobot UART port
	const bool pause								///< [in] TRUE if set to pause
);

/// begin a sensor stream containing all sensors (SensorGroup6)
///
///	\warning Do not use this to measure distance and angle,
///	as these measurements are subject to roundoff
///	error in each packet; less frequent packets (polling)
///	are needed.
/// \return error code
int32_t irobotSensorStreamStartAll(
	const irobotUARTPort_t			port			///< [in] irobot UART port
);

/// process a sensors stream that has been configured
/// to transmit SensorGroup6 (all sensors)
int32_t irobotSensorStreamProcessAll(
	xqueue_t * const queue,							///< [in/out] raw byte stream
	irobotSensorGroup6_t * const sensors,			///< [out] sensors
	bool * const packetFound						///< [out] packet found
);


#endif /// _IROBOTSTREAM_H
