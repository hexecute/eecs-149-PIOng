/** \file irobotActuator.h
 *
 * iRobot Create actuator functions.
 *
 * \author Jeff C. Jensen
 * \date 2013-10-17
 * \copyright Copyright (C) 2013, Jeff C. Jensen, Edward A. Lee, and Sanjit A. Seshia.
 * 			  This software accompanies An Introductory Lab in Embedded and Cyber-Physical Systems
 * 			  and is licensed under a Creative Commons Attribution-NonCommercial-NoDerivs 3.0
 * 			  Unported License. See http://leeseshia.org/lab.
 */

#ifndef _IROBOTACTUATOR_H
#define _IROBOTACTUATOR_H

#include "irobotError.h"
#include "irobotOpcode.h"
#include "irobotActuatorTypes.h"
#include "irobotUART.h"

/// Write to the digital output bank of the cargo bay on iRobot.
/// \return error code
int32_t irobotDigitalOutputs(
	const irobotUARTPort_t	port,		///< [in] UART port
	const uint8_t			output 		///< [in] Pins 0-7
);

/// Directly actuate left and right wheels.
/// \return error code
int32_t irobotDriveDirect(
	const irobotUARTPort_t	port,			///< [in] UART port
	int16_t					leftWheelSpeed,	///< [in] Left wheels speed, in mm/s
	int16_t					rightWheelSpeed ///< [in] Right wheel speed, in mm/s
);

/// Drives in a fixed direction
/// \return error code
int32_t irobotDriveDirection(
	const irobotUARTPort_t		port,		///< [in] UART port
	int16_t						velocity,	///< [in] Velocity, in mm/s
	const irobotDirection_t		direction	///< [in] direction
);

/// Drive the robot with a fixed linear speed, and turning through a fixed radius.
/// \warning Do not call this function for the special cases of driving straight, or clockwise
/// and counter-clockwise turning; this function instructs the robot to drive only nonzero radii.
/// \return error code
int32_t irobotDriveRadius(
	const irobotUARTPort_t	port,		///< [in] UART port
	int16_t					velocity,	///< [in] Velocity, in mm/s
	int16_t					radius		///< [in] Radius, in mm
);

/// Change the state of the iRobot power, play, and advance LEDs.
/// \return error code
int32_t irobotLEDs(
	const irobotUARTPort_t	port,			///< [in] UART port
	const irobotLED_t		leds,			///< [in] LEDs to turn on
	const uint8_t			powerColor,		///< [in] Power LED color (G[0] - R[255])
	const uint8_t			powerIntensity	///< [in] Power LED intensiy (0-255)
);

/// Set the PWM duty cycle of the low-side drivers.
/// \return error code
int32_t irobotPWMLowSideDrivers(
	const irobotUARTPort_t	port,		///< [in] UART port
	uint8_t					pwm0,		///< [in] PWM for low-side driver 0 (0-128 duty cycle)
	uint8_t					pwm1,		///< [in] PWM for low-side driver 1 (0-128 duty cycle)
	uint8_t					pwm2		///< [in] PWM for low-side driver 2 (0-128 duty cycle)
);

/// Define a song. Each song is alloted 16 notes, but a song can "spill over" into
/// the next if so desired. The maximum number of notes that may be defined is
/// (16 - SongNumber) * 16.
/// \return error code
int32_t irobotSong(
	const irobotUARTPort_t			port,		///< [in] UART port
	uint8_t							songNumber,	///< [in] Song number
	const irobotSongNote_t * const	songNotes,	///< [in] Song notes
	uint8_t							nNotes		///< [in] Number of song notes
);

/// Play a song
/// \return error code
int32_t irobotPlaySong(
	const irobotUARTPort_t	port,		///< [in] UART port
	const uint8_t			songNumber	///< [in] Song number
);

/// Stops the wheels.
/// \return error code
int32_t irobotStop(
	const irobotUARTPort_t	port		///< [in] UART port
);


#endif	// _IROBOTACTUATOR_H
