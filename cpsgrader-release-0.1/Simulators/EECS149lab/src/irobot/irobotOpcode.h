/** \file irobotOpcode.h
 *
 * iRobot Open Interface Operation Codes (opcodes)
 *
 * \author Jeff C. Jensen
 * \date 2013-12-09
 * \copyright Copyright (C) 2013, Jeff C. Jensen, Edward A. Lee, and Sanjit A. Seshia.
 * 			  This software accompanies An Introductory Lab in Embedded and Cyber-Physical Systems
 * 			  and is licensed under a Creative Commons Attribution-NonCommercial-NoDerivs 3.0
 * 			  Unported License. See http://leeseshia.org/lab.
 */

#ifndef _IROBOTOPCODE_H
#define _IROBOTOPCODE_H

/// OpCodes for iRobot open interface
typedef enum{
	OP_START				= 128,	///< Start mode
	OP_BAUD					= 129,	///< Change baud rate
	OP_CONTROL				= 130,	///< Control mode
	OP_SAFE					= 131,	///< Safe mode
	OP_FULL					= 132,	///< Full mode
	OP_DEMO					= 136,	///< Demo mode
	OP_DEMO_COVER			= 135,	///< Cover demo
	OP_DEMO_COVER_DOCK		= 143,	///< Dock & cover demo
	OP_DEMO_SPOT			= 134,	///< Spot demo
	OP_DRIVE				= 137,	///< Drive a turn radius and speed
	OP_DRIVE_DIRECT			= 145,	///< Directly drive left and right wheels
	OP_LEDS					= 139,	///< Control LEDs
	OP_DIGITAL_OUTPUTS		= 147,	///< Write digital outputs
	OP_PWM_LOW_SIDE_DRIVERS	= 144,	///< Write PWM low-side drivers
	OP_LOW_SIDE_DRIVERS		= 138,	///< Write analog low-side drivers
	OP_SEND_IR				= 151,	///< Send IR signal
	OP_SONG					= 140,	///< Define song
	OP_PLAY_SONG			= 141,	///< Play song
	OP_SENSORS				= 142,	///< Query sensors
	OP_QUERY_LIST			= 149,	///< Set list of sensors to query
	OP_STREAM				= 148,	///< Sensor stream
	OP_PAUSE_RESUME_STREAM	= 150,	///< Pause or resume sensor stream
	OP_SCRIPT				= 152,	///< Define action script
	OP_PLAY_SCRIPT			= 153,	///< Play action script
	OP_SHOW_SCRIPT			= 154,	///< Read the current action script
	OP_WAIT_TIME			= 155,	///< Script: instruct the robot to wait for a specified time
	OP_WAIT_DISTANCE		= 156,	///< Script: instruct the robot to wait for a specified distance
	OP_WAIT_ANGLE			= 157,	///< Script: instruct the robot to wait for a specified angle
	OP_WAIT_EVENT			= 158	///< Script: instruct the robot to wait for an event
} irobotOpcode_t;

#define OP_START_SIZE					1	///< Size of the START opcode and payload
#define OP_BAUD_SIZE					2	///< Size of the BAUD opcode and payload
#define OP_CONTROL_SIZE					1	///< Size of the CONTROL opcode and payload
#define OP_SAFE_SIZE					1	///< Size of the SAFE opcode and payload
#define OP_FULL_SIZE					1	///< Size of the FULL opcode and payload
#define OP_DEMO_SIZE					2	///< Size of the DEMO opcode and payload
#define OP_DEMO_COVER_SIZE				1	///< Size of the DEMO_COVER opcode and payload
#define OP_DEMO_COVER_DOCK_SIZE			1	///< Size of the DEMO_COVER_DOCK opcode and payload
#define OP_DEMO_SPOT_SIZE				1	///< Size of the DEMO_SPOT opcode and payload
#define OP_DRIVE_SIZE					5	///< Size of the DRIVE opcode and payload
#define OP_DRIVE_DIRECT_SIZE			5	///< Size of the DRIVE_DIRECT opcode and payload
#define OP_LEDS_SIZE					4	///< Size of the LEDs opcode and payload
#define OP_DIGITAL_OUTPUTS_SIZE			2	///< Size of the DIGITAL_OUTPUTS opcode and payload
#define OP_PWM_LOW_SIDE_DRIVERS_SIZE	4	///< Size of the PWM_LOW_SIDE_DRIVERS opcode and payload
#define OP_LOW_SIDE_DRIVERS_SIZE		2	///< Size of the LOW_SIDE_DRIVERS opcode and payload
#define OP_SEND_IR_SIZE					2	///< Size of the SEND_IR opcode and payload
// OP_SONG size is variable
#define OP_PLAY_SONG_SIZE				2	///< Size of the PLAY_SONG opcode and payload
#define OP_SENSORS_SIZE					2	///< Size of the SENSORS opcode and payload
// OP_QUERY_LIST size is variable
// OP_STREAM size is variable
#define OP_PAUSE_RESUME_STREAM_SIZE		2	///< Size of the PAUSE_RESUME_STREAM opcode and payload
// OP_SCRIPT size is variable
#define OP_PLAY_SCRIPT_SIZE				1	///< Size of the PLAY_SCRIPT opcode and payload
#define OP_SHOW_SCRIPT_SIZE				1	///< Size of the SHOW_SCRIPT opcode and payload
#define OP_WAIT_TIME_SIZE				2	///< Size of the WAIT_TIME opcode and payload
#define OP_WAIT_DISTANCE_SIZE			3	///< Size of the WAIT_DISTANCE opcode and payload
#define OP_WAIT_ANGLE_SIZE				3	///< Size of the WAIT_ANGLE opcode and payload
#define OP_WAIT_EVENT_SIZE				2	///< Size of the WAIT_EVENT opcode and payload

#endif	// _IROBOTOPCODE_H
