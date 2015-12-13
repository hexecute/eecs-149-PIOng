#include "irobotActuator.h"
#include <stdlib.h>

#ifndef MAX
	#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#endif
#ifndef MIN
	#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#endif
#ifndef coerce
	#define coerce(xMin, x, xMax)	(MIN(MAX(xMin, x), xMax))
#endif

int32_t irobotDigitalOutputs(
	const irobotUARTPort_t	port,
	const uint8_t			output
){
	uint8_t packet[OP_DIGITAL_OUTPUTS_SIZE];
	
	packet[0] = OP_DIGITAL_OUTPUTS;
	packet[1] = output;

	return irobotUARTWriteRaw(port, packet, OP_DIGITAL_OUTPUTS_SIZE);
}

int32_t irobotDriveDirect(
	const irobotUARTPort_t	port,
	int16_t					leftWheelSpeed,
	int16_t					rightWheelSpeed
){
	uint8_t packet[OP_DRIVE_DIRECT_SIZE];
	
	leftWheelSpeed = (int16_t)coerce(ACTUATOR_WHEEL_SPEED_MIN, leftWheelSpeed, ACTUATOR_WHEEL_SPEED_MAX);
	rightWheelSpeed = (int16_t)coerce(ACTUATOR_WHEEL_SPEED_MIN, rightWheelSpeed, ACTUATOR_WHEEL_SPEED_MAX);

	packet[0] = OP_DRIVE_DIRECT;
	packet[1] = HO(rightWheelSpeed);
	packet[2] = LO(rightWheelSpeed);
	packet[3] = HO(leftWheelSpeed);
	packet[4] = LO(leftWheelSpeed);

	return irobotUARTWriteRaw(port, packet, OP_DRIVE_DIRECT_SIZE);
}

int32_t irobotDriveDirection(
	const irobotUARTPort_t		port,
	int16_t						velocity,
	const irobotDirection_t		direction
){
	uint8_t packet[OP_DRIVE_SIZE];
	
	velocity = (int16_t)coerce(ACTUATOR_WHEEL_SPEED_MIN, velocity, ACTUATOR_WHEEL_SPEED_MAX);

	packet[0] = OP_DRIVE;
	packet[1] = HO(velocity);
	packet[2] = LO(velocity);
	packet[3] = HO((uint16_t)direction);
	packet[4] = LO((uint16_t)direction);

	return irobotUARTWriteRaw(port, packet, OP_DRIVE_SIZE);
}

int32_t irobotDriveRadius(
	const irobotUARTPort_t	port,
	int16_t					velocity,
	int16_t					radius
){
	uint8_t packet[OP_DRIVE_SIZE];

	velocity = (int16_t)coerce(ACTUATOR_WHEEL_SPEED_MIN, velocity, ACTUATOR_WHEEL_SPEED_MAX);
	radius = (int16_t)coerce(ACTUATOR_DRIVE_RADIUS_MIN, radius, ACTUATOR_DRIVE_RADIUS_MAX);

	// Special case: radius = 1mm is interpreted as CCW rotation;
	//	iRobot Drive CCW covers this case, so a drive radius of 1mm is
	//	interpreted as the next smallest radius, 2mm
	if(radius == 1){
		radius = 2;
	}

	packet[0] = OP_DRIVE;
	packet[1] = HO(velocity);
	packet[2] = LO(velocity);
	packet[3] = HO(radius);
	packet[4] = LO(radius);
	
	return irobotUARTWriteRaw(port, packet, OP_DRIVE_SIZE);
}

int32_t irobotLEDs(
	const irobotUARTPort_t	port,
	const irobotLED_t		leds,
	const uint8_t			powerColor,
	const uint8_t			powerIntensity
){
	uint8_t packet[OP_LEDS_SIZE];

	packet[0] = OP_LEDS;
	packet[1] = (uint8_t)leds;
	packet[2] = powerColor;
	packet[3] = powerIntensity;
	
	return irobotUARTWriteRaw(port, packet, OP_LEDS_SIZE);
}

int32_t irobotPWMLowSideDrivers(
	const irobotUARTPort_t	port,
	uint8_t					pwm0,
	uint8_t					pwm1,
	uint8_t					pwm2
){
	uint8_t packet[OP_PWM_LOW_SIDE_DRIVERS_SIZE];

	pwm0 = (uint16_t)coerce(ACTUATOR_PWM_DUTY_MIN, pwm0, ACTUATOR_PWM_DUTY_MAX);
	pwm1 = (uint16_t)coerce(ACTUATOR_PWM_DUTY_MIN, pwm1, ACTUATOR_PWM_DUTY_MAX);
	pwm2 = (uint16_t)coerce(ACTUATOR_PWM_DUTY_MIN, pwm2, ACTUATOR_PWM_DUTY_MAX);

	packet[0] = OP_PWM_LOW_SIDE_DRIVERS;
	packet[1] = pwm0;
	packet[2] = pwm1;
	packet[3] = pwm2;
	
	return irobotUARTWriteRaw(port, packet, OP_PWM_LOW_SIDE_DRIVERS_SIZE);
}

/// opcode + song number + song length + n notes
#define OP_SONG_MAX_LENGTH	(ACTUATOR_MAX_SONGS * ACTUATOR_MAX_NOTES_PER_SONG + 3)

int32_t irobotSong(
	const irobotUARTPort_t			port,
	uint8_t							songNumber,
	const irobotSongNote_t * const	songNotes,
	uint8_t							nNotes
){
	uint8_t packet[OP_SONG_MAX_LENGTH];
	uint8_t packetIndex = 0;
	uint8_t noteIndex = 0;

	if(!songNotes){
		return ERROR_INVALID_PARAMETER;
	}

	songNumber = MIN(songNumber, ACTUATOR_MAX_SONGS - 1);
	nNotes = MIN(nNotes, (ACTUATOR_MAX_SONGS - songNumber) * ACTUATOR_MAX_NOTES_PER_SONG);

	packet[packetIndex++] = OP_SONG;
	packet[packetIndex++] = songNumber;
	packet[packetIndex++] = nNotes;
	for(noteIndex = 0; noteIndex < nNotes; noteIndex++){
		packet[packetIndex++] = songNotes[noteIndex].midiNote;
		packet[packetIndex++] = songNotes[noteIndex].duration;
	}
	
	return irobotUARTWriteRaw(port, packet, packetIndex);
}

int32_t irobotPlaySong(
	const irobotUARTPort_t	port,
	const uint8_t			songNumber
){
	uint8_t packet[OP_PLAY_SONG_SIZE];

	packet[0] = OP_PLAY_SONG;
	packet[1] = songNumber;
	
	return irobotUARTWriteRaw(port, packet, OP_PLAY_SONG_SIZE);
}

int32_t irobotStop(
	const irobotUARTPort_t	port
){
	return irobotDriveDirect(port, 0, 0);
}
