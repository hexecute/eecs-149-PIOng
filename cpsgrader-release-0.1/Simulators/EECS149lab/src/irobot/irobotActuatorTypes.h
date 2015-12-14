/** \file irobotActuatorTypes.h
 *
 * iRobot actuator type definitions.
 *
 * \author Jeff C. Jensen
 * \date 2013-12-09
 * \copyright Copyright (C) 2013, Jeff C. Jensen, Edward A. Lee, and Sanjit A. Seshia.
 * 			  This software accompanies An Introductory Lab in Embedded and Cyber-Physical Systems
 * 			  and is licensed under a Creative Commons Attribution-NonCommercial-NoDerivs 3.0
 * 			  Unported License. See http://leeseshia.org/lab.
 */

#ifndef _IROBOTACTUATORTYPES_H
#define _IROBOTACTUATORTYPES_H

#include "irobotTypes.h"

/// iRobot drive directions
typedef enum{
	DRIVE_STRAIGHT			= 0x8000,	///< straight
	DRIVE_CLOCKWISE			= 0xFFFF,	///< clockwise
	DRIVE_COUNTERCLOCKWISE	= 0x0001	///< counter-clockwise
} irobotDirection_t;

/// iRobot LED selector
typedef enum{
	LED_NONE			= 0,	///< none
	LED_PLAY			= 2,	///< play
	LED_ADVANCE			= 8,	///< advance
	LED_ADVANCE_PLAY	= 10	///< advance and play
} irobotLED_t;

/// iRobot song note
typedef struct{
	uint8_t midiNote;	///< MIDI note
	uint8_t duration;	///< note duration
} irobotSongNote_t;

/// max wheel speed, in mm/s
#define ACTUATOR_WHEEL_SPEED_MAX			500
/// min wheel speed, in mm/s
#define ACTUATOR_WHEEL_SPEED_MIN			-500

/// max drive radius, in mm
#define ACTUATOR_DRIVE_RADIUS_MAX			2000
/// min drive radius, in mm
#define ACTUATOR_DRIVE_RADIUS_MIN			-2000

/// max PWM duty cycle (100%)
#define ACTUATOR_PWM_DUTY_MAX				128
/// min PWM duty cycle (0%)
#define ACTUATOR_PWM_DUTY_MIN				0

/// max number of songs that may be defined
#define ACTUATOR_MAX_SONGS					16
/// max number of notes per song
#define ACTUATOR_MAX_NOTES_PER_SONG			16


#endif	// _IROBOTTYPES_H
