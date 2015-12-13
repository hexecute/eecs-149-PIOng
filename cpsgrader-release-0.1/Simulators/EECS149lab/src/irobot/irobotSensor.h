/** \file irobotSensor.h
 *
 * iRobot Create sensor operations.
 *
 * \author Jeff C. Jensen
 * \date 2013-12-09
 * \copyright Copyright (C) 2013, Jeff C. Jensen, Edward A. Lee, and Sanjit A. Seshia.
 * 			  This software accompanies An Introductory Lab in Embedded and Cyber-Physical Systems
 * 			  and is licensed under a Creative Commons Attribution-NonCommercial-NoDerivs 3.0
 * 			  Unported License. See http://leeseshia.org/lab.
*/

#ifndef _IROBOTSENSOR_H
#define _IROBOTSENSOR_H

#include "irobotSensorTypes.h"
#include "irobotError.h"
#include "xqueue.h"

/// read a sensor from a data queue
/// \return error code
int32_t irobotReadBumps_Wheeldrops(
	xqueue_t * const queue,									///< [in/out] queue containing sensor packet
	irobotBumps_WheelDrops_t * const bumps_wheelDrops		///< [out] sensor value
);

/// read a sensor from a data queue
/// \return error code
int32_t irobotReadButtons(
	xqueue_t * const queue,			///< [in/out] queue containing sensor packet
	irobotButtons_t * const buttons	///< [out] sensor value
);

/// read a sensor from a data queue
/// \return error code
int32_t irobotReadCargoBayDigitalInputs(
	xqueue_t * const queue,								///< [in/out] queue containing sensor packet
	irobotCargoBayDigitalInputs_t * const digitalInputs	///< [out] sensor value
);

/// read a sensor from a data queue
/// \return error code
int32_t irobotReadChargingSourcesAvailable(
	xqueue_t * const queue,								///< [in/out] queue containing sensor packet
	irobotChargingSourcesAvailable_t * const sources	///< [out] sensor value
);

/// read a sensor from a data queue
/// \return error code
int32_t irobotReadLowSideDriver_WheelOvercurrent(
	xqueue_t * const queue,										///< [in/out] queue containing sensor packet
	irobotLowSideDriver_WheelOvercurrent_t * const lsd_wo		///< [out] sensor value
);

/// read a sensor group from a data queue
/// \return error code
int32_t irobotReadSensorGroup0(
	xqueue_t * const queue,						///< [in/out] queue containing sensor packet
	irobotSensorGroup0_t * const sensorGroup0	///< [out] sensor value
);

/// read a sensor group from a data queue
/// \return error code
int32_t irobotReadSensorGroup1(
	xqueue_t * const queue,						///< [in/out] queue containing sensor packet
	irobotSensorGroup1_t * const sensorGroup1	///< [out] sensor value
);

/// read a sensor group from a data queue
/// \return error code
int32_t irobotReadSensorGroup2(
	xqueue_t * const queue,						///< [in/out] queue containing sensor packet
	irobotSensorGroup2_t * const sensorGroup2	///< [out] sensor value
);

/// read a sensor group from a data queue
/// \return error code
int32_t irobotReadSensorGroup3(
	xqueue_t * const queue,						///< [in/out] queue containing sensor packet
	irobotSensorGroup3_t * const sensorGroup3	///< [out] sensor value
);

/// read a sensor group from a data queue
/// \return error code
int32_t irobotReadSensorGroup4(
	xqueue_t * const queue,						///< [in/out] queue containing sensor packet
	irobotSensorGroup4_t * const sensorGroup4	///< [out] sensor value
);

/// read a sensor group from a data queue
/// \return error code
int32_t irobotReadSensorGroup5(
	xqueue_t * const queue,						///< [in/out] queue containing sensor packet
	irobotSensorGroup5_t * const sensorGroup5	///< [out] sensor value
);

/// read a sensor group from a data queue
/// \return error code
int32_t irobotReadSensorGroup6(
	xqueue_t * const queue,						///< [in/out] queue containing sensor packet
	irobotSensorGroup6_t * const sensorGroup6	///< [out] sensor value
);

/// print all irobot sensors
/// \return error code
int32_t irobotPrintSensorGroup6(
	const irobotSensorGroup6_t * const sensors
);


#endif	/// _IROBOTSENSOR_H
