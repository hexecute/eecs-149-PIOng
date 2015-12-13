#include "irobotSensor.h"
#include <stdio.h>

int32_t irobotReadBumps_Wheeldrops(
	xqueue_t * const queue,
	irobotBumps_WheelDrops_t * const bumps_wheelDrops
){
	uint8_t packedValues = 0;

	//check for NULL pointers
	if(!queue || !bumps_wheelDrops){
		return ERROR_INVALID_PARAMETER;
	}
	//verify packet size
	if(xqueue_count(queue) < SENSOR_BUMPS_WHEELDROPS_SIZE){
		return ERROR_INVALID_PARAMETER;
	}

	packedValues = xqueue_pop(queue);

	bumps_wheelDrops->bumpRight = !!(packedValues & (1 << 0));
	bumps_wheelDrops->bumpLeft = !!(packedValues & (1 << 1));
	bumps_wheelDrops->wheeldropRight = !!(packedValues & (1 << 2));
	bumps_wheelDrops->wheeldropLeft = !!(packedValues & (1 << 3));
	bumps_wheelDrops->wheeldropCaster = !!(packedValues & (1 << 4));

	return ERROR_SUCCESS;
}

int32_t irobotReadButtons(
	xqueue_t * const queue,
	irobotButtons_t * const buttons
){
	uint8_t packedValues = 0;

	//check for NULL pointers
	if(!queue || !buttons){
		return ERROR_INVALID_PARAMETER;
	}
	//verify packet size
	if(xqueue_count(queue) < SENSOR_BUTTONS_SIZE){
		return ERROR_INVALID_PARAMETER;
	}

	packedValues = xqueue_pop(queue);

	buttons->play = !!(packedValues & (1 << 0));
	buttons->advance = !!(packedValues & (1 << 2));

	return ERROR_SUCCESS;
}

int32_t irobotReadCargoBayDigitalInputs(
	xqueue_t * const queue,
	irobotCargoBayDigitalInputs_t * const digitalInputs
){
	uint8_t packedValues = 0;

	//check for NULL pointers
	if(!queue || !digitalInputs){
		return ERROR_INVALID_PARAMETER;
	}
	//verify packet size
	if(xqueue_count(queue) < SENSOR_CARGO_BAY_DIGITAL_INPUTS_SIZE){
		return ERROR_INVALID_PARAMETER;
	}

	packedValues = xqueue_pop(queue);

	digitalInputs->digitalInput0 = !!(packedValues & (1 << 0));
	digitalInputs->digitalInput1 = !!(packedValues & (1 << 1));
	digitalInputs->digitalInput2 = !!(packedValues & (1 << 2));
	digitalInputs->digitalInput3 = !!(packedValues & (1 << 3));
	digitalInputs->deviceDetect = !!(packedValues & (1 << 4));

	return ERROR_SUCCESS;
}

int32_t irobotReadChargingSourcesAvailable(
	xqueue_t * const queue,
	irobotChargingSourcesAvailable_t * const sources
){
	uint8_t packedValues = 0;
	//check for NULL pointers
	if(!queue || !sources){
		return ERROR_INVALID_PARAMETER;
	}
	//verify packet size
	if(xqueue_count(queue) < SENSOR_CHARGING_SOURCES_AVAILABLE_SIZE){
		return ERROR_INVALID_PARAMETER;
	}

	packedValues = xqueue_pop(queue);

	sources->internalCharger = !!(packedValues & (1 << 0));
	sources->homeBase = !!(packedValues & (1 << 1));

	return ERROR_SUCCESS;
}

int32_t irobotReadLowSideDriver_WheelOvercurrent(
	xqueue_t * const queue,
	irobotLowSideDriver_WheelOvercurrent_t * const lsd_wo
){
	uint8_t packedValues = 0;

	//check for NULL pointers
	if(!queue || !lsd_wo){
		return ERROR_INVALID_PARAMETER;
	}
	//verify packet size
	if(xqueue_count(queue) < SENSOR_LOW_SIDE_DRIVER_WHEEL_OVERDRIVE_SIZE){
		return ERROR_INVALID_PARAMETER;
	}

	packedValues = xqueue_pop(queue);

	lsd_wo->lowSideDriver1 = !!(packedValues & (1 << 0));
	lsd_wo->lowSideDriver0 = !!(packedValues & (1 << 1));
	lsd_wo->lowSideDriver2 = !!(packedValues & (1 << 2));
	lsd_wo->rightWheel = !!(packedValues & (1 << 3));
	lsd_wo->leftWheel = !!(packedValues & (1 << 4));

	return ERROR_SUCCESS;
}

int32_t irobotReadSensorGroup0(
	xqueue_t * const queue,
	irobotSensorGroup0_t * const sensorGroup0
){
	int32_t status = ERROR_SUCCESS;

	//0 = 1 + 2 + 3
	//at least in the binary field where 2:=1+1=0, 3:=2+1=1
	irobotSensorGroup1_t	sensorGroup1 = {{0}};
	irobotSensorGroup2_t	sensorGroup2 = {0};
	irobotSensorGroup3_t	sensorGroup3 = {0};

	//check for NULL pointers
	if(!queue || !sensorGroup0){
		return ERROR_INVALID_PARAMETER;
	}
	//verify packet size
	if(xqueue_count(queue) < SENSOR_GROUP0_SIZE){
		return ERROR_INVALID_PARAMETER;
	}

	if(!irobot_IsError(status)){
		irobot_StatusMerge(&status, irobotReadSensorGroup1(queue, &sensorGroup1));
	}
	if(!irobot_IsError(status)){
		irobot_StatusMerge(&status, irobotReadSensorGroup2(queue, &sensorGroup2));
	}
	if(!irobot_IsError(status)){
		irobot_StatusMerge(&status, irobotReadSensorGroup3(queue, &sensorGroup3));
	}
	if(!irobot_IsError(status)){
		sensorGroup0->bumps_wheelDrops = sensorGroup1.bumps_wheelDrops;
		sensorGroup0->wall = sensorGroup1.wall;
		sensorGroup0->cliffLeft = sensorGroup1.cliffLeft;
		sensorGroup0->cliffFrontLeft = sensorGroup1.cliffFrontLeft;
		sensorGroup0->cliffFrontRight = sensorGroup1.cliffFrontRight;
		sensorGroup0->cliffRight = sensorGroup1.cliffRight;
		sensorGroup0->virtualWall = sensorGroup1.virtualWall;
		sensorGroup0->lowSideDriver_WheelOvercurrent = sensorGroup1.lowSideDriver_wheelovercurrent;

		sensorGroup0->infrared = sensorGroup2.infrared;
		sensorGroup0->buttons = sensorGroup2.buttons;
		sensorGroup0->distance = sensorGroup2.distance;
		sensorGroup0->angle = sensorGroup2.angle;

		sensorGroup0->chargingState = sensorGroup3.chargingState;
		sensorGroup0->voltage = sensorGroup3.voltage;
		sensorGroup0->current = sensorGroup3.current;
		sensorGroup0->batteryTemperature = sensorGroup3.batteryTemperature;
		sensorGroup0->batteryCharge = sensorGroup3.batteryCharge;
		sensorGroup0->batteryCapacity = sensorGroup3.batteryCapacity;
	}

	return status;
}

int32_t irobotReadSensorGroup1(
	xqueue_t * const queue,
	irobotSensorGroup1_t * const sensorGroup1
){
	int32_t status = ERROR_SUCCESS;
	//check for NULL pointers
	if(!queue || !sensorGroup1){
		return ERROR_INVALID_PARAMETER;
	}
	//verify packet size
	if(xqueue_count(queue) < SENSOR_GROUP1_SIZE){
		return ERROR_INVALID_PARAMETER;
	}

	if(!irobot_IsError(status)){
		irobot_StatusMerge(&status, irobotReadBumps_Wheeldrops(queue, &sensorGroup1->bumps_wheelDrops));
	}

	if(!irobot_IsError(status)){
		sensorGroup1->wall				= (bool)xqueue_pop(queue);
		sensorGroup1->cliffLeft			= (bool)xqueue_pop(queue);
		sensorGroup1->cliffFrontLeft	= (bool)xqueue_pop(queue);
		sensorGroup1->cliffFrontRight	= (bool)xqueue_pop(queue);
		sensorGroup1->cliffRight		= (bool)xqueue_pop(queue);
		sensorGroup1->virtualWall		= (bool)xqueue_pop(queue);
	}
	
	if(!irobot_IsError(status)){
		irobot_StatusMerge(&status, irobotReadLowSideDriver_WheelOvercurrent(queue, &sensorGroup1->lowSideDriver_wheelovercurrent));
	}

	xqueue_drop_many(queue, 2);	//unused

	return status;
}

int32_t irobotReadSensorGroup2(
	xqueue_t * const queue,
	irobotSensorGroup2_t * const sensorGroup2
){
	int32_t status = ERROR_SUCCESS;

	//check for NULL pointers
	if(!queue || !sensorGroup2){
		return ERROR_INVALID_PARAMETER;
	}
	//verify packet size
	if(xqueue_count(queue) < SENSOR_GROUP2_SIZE){
		return ERROR_INVALID_PARAMETER;
	}

	if(!irobot_IsError(status)){
		sensorGroup2->infrared = xqueue_pop(queue);
		irobot_StatusMerge(&status, irobotReadButtons(queue, &sensorGroup2->buttons));
	}
	if(!irobot_IsError(status)){
		sensorGroup2->distance = (int16_t)xqueue_pop16(queue);
		sensorGroup2->angle = (int16_t)xqueue_pop16(queue);
	}

	return status;
}

int32_t irobotReadSensorGroup3(
	xqueue_t * const queue,
	irobotSensorGroup3_t * const sensorGroup3
){
	//check for NULL pointers
	if(!queue || !sensorGroup3){
		return ERROR_INVALID_PARAMETER;
	}
	//verify packet size
	if(xqueue_count(queue) < SENSOR_GROUP3_SIZE){
		return ERROR_INVALID_PARAMETER;
	}

	sensorGroup3->chargingState		= (irobotChargingState_t)xqueue_pop(queue);
	sensorGroup3->voltage			= xqueue_pop16(queue);
	sensorGroup3->current			= (int16_t)xqueue_pop16(queue);
	sensorGroup3->batteryTemperature= (int8_t)xqueue_pop(queue);
	sensorGroup3->batteryCharge		= xqueue_pop16(queue);
	sensorGroup3->batteryCapacity	= xqueue_pop16(queue);
	
	return ERROR_SUCCESS;
}

int32_t irobotReadSensorGroup4(
	xqueue_t * const queue,
	irobotSensorGroup4_t * const sensorGroup4
){
	int32_t status = ERROR_SUCCESS;
	//check for NULL pointers
	if(!queue || !sensorGroup4){
		return ERROR_INVALID_PARAMETER;
	}
	//verify packet size
	if(xqueue_count(queue) < SENSOR_GROUP4_SIZE){
		return ERROR_INVALID_PARAMETER;
	}

	if(!irobot_IsError(status)){
		sensorGroup4->wallSignal			= xqueue_pop16(queue);
		sensorGroup4->cliffLeftSignal		= xqueue_pop16(queue);
		sensorGroup4->cliffFrontLeftSignal	= xqueue_pop16(queue);
		sensorGroup4->cliffFrontRightSignal	= xqueue_pop16(queue);
		sensorGroup4->cliffRightSignal		= xqueue_pop16(queue);

		irobot_StatusMerge(&status, irobotReadCargoBayDigitalInputs(queue, &sensorGroup4->cargoBayDigitalInputs));
	}
	if(!irobot_IsError(status)){
		irobot_StatusMerge(&status, irobotReadChargingSourcesAvailable(queue, &sensorGroup4->chargingSourcesAvailable));
	}
	if(!irobot_IsError(status)){
		sensorGroup4->cargoBayAnalogSignal	= xqueue_pop16(queue);
	}

	return status;
}

int32_t irobotReadSensorGroup5(
	xqueue_t * const queue,
	irobotSensorGroup5_t * const sensorGroup5
){
	//check for NULL pointers
	if(!queue || !sensorGroup5){
		return ERROR_INVALID_PARAMETER;
	}
	//verify packet size
	if(xqueue_count(queue) < SENSOR_GROUP5_SIZE){
		return ERROR_INVALID_PARAMETER;
	}

	sensorGroup5->oiState						= (irobotOIState_t)xqueue_pop(queue);
	sensorGroup5->songNumber					= xqueue_pop(queue);
	sensorGroup5->songPlaying					= (bool)xqueue_pop(queue);
	sensorGroup5->nStreamPackets				= xqueue_pop(queue);
	sensorGroup5->requestedVelocity				= (int16_t)xqueue_pop16(queue);
	sensorGroup5->requestedRadius				= (int16_t)xqueue_pop16(queue);
	sensorGroup5->requestedRightWheelVelocity	= (int16_t)xqueue_pop16(queue);
	sensorGroup5->requestedLeftWheelVelocity	= (int16_t)xqueue_pop16(queue);

	return ERROR_SUCCESS;
}

int32_t irobotReadSensorGroup6(
	xqueue_t * const queue,
	irobotSensorGroup6_t * const sensorGroup6
){
	int32_t status = ERROR_SUCCESS;
	
	//6 = 1 + 2 + 3 + 4 + 5  = 0 + 4 + 5
	irobotSensorGroup0_t	sensorGroup0 = {{0}};
	irobotSensorGroup4_t	sensorGroup4 = {0};
	irobotSensorGroup5_t	sensorGroup5 = {0};

	//check for NULL pointers
	if(!queue || !sensorGroup6){
		return ERROR_INVALID_PARAMETER;
	}
	//verify packet size
	if(xqueue_count(queue) < SENSOR_GROUP6_SIZE){
		return ERROR_INVALID_PARAMETER;
	}

	if(!irobot_IsError(status)){
		irobot_StatusMerge(&status, irobotReadSensorGroup0(queue, &sensorGroup0));
	}
	if(!irobot_IsError(status)){
		irobot_StatusMerge(&status, irobotReadSensorGroup4(queue, &sensorGroup4));
	}
	if(!irobot_IsError(status)){
		irobot_StatusMerge(&status, irobotReadSensorGroup5(queue, &sensorGroup5));
	}
	if(!irobot_IsError(status)){
		sensorGroup6->bumps_wheelDrops = sensorGroup0.bumps_wheelDrops;
		sensorGroup6->wall = sensorGroup0.wall;
		sensorGroup6->cliffLeft = sensorGroup0.cliffLeft;
		sensorGroup6->cliffFrontLeft = sensorGroup0.cliffFrontLeft;
		sensorGroup6->cliffFrontRight = sensorGroup0.cliffFrontRight;
		sensorGroup6->cliffRight = sensorGroup0.cliffRight;
		sensorGroup6->virtualWall = sensorGroup0.virtualWall;
		sensorGroup6->lowSideDriver_WheelOvercurrent = sensorGroup0.lowSideDriver_WheelOvercurrent;

		sensorGroup6->infrared = sensorGroup0.infrared;
		sensorGroup6->buttons = sensorGroup0.buttons;
		sensorGroup6->distance = sensorGroup0.distance;
		sensorGroup6->angle = sensorGroup0.angle;

		sensorGroup6->chargingState = sensorGroup0.chargingState;
		sensorGroup6->voltage = sensorGroup0.voltage;
		sensorGroup6->current = sensorGroup0.current;
		sensorGroup6->batteryTemperature = sensorGroup0.batteryTemperature;
		sensorGroup6->batteryCharge = sensorGroup0.batteryCharge;
		sensorGroup6->batteryCapacity = sensorGroup0.batteryCapacity;

		sensorGroup6->wallSignal = sensorGroup4.wallSignal;
		sensorGroup6->cliffLeftSignal = sensorGroup4.cliffLeftSignal;
		sensorGroup6->cliffFrontLeftSignal = sensorGroup4.cliffFrontLeftSignal;
		sensorGroup6->cliffFrontRightSignal = sensorGroup4.cliffFrontRightSignal;
		sensorGroup6->cliffRightSignal = sensorGroup4.cliffRightSignal;
		sensorGroup6->cargoBayDigitalInputs = sensorGroup4.cargoBayDigitalInputs;
		sensorGroup6->cargoBayAnalogSignal = sensorGroup4.cargoBayAnalogSignal;
		sensorGroup6->chargingSourcesAvailable = sensorGroup4.chargingSourcesAvailable;

		sensorGroup6->oiState = sensorGroup5.oiState;
		sensorGroup6->songNumber = sensorGroup5.songNumber;
		sensorGroup6->songPlaying = sensorGroup5.songPlaying;
		sensorGroup6->nStreamPackets = sensorGroup5.nStreamPackets;
		sensorGroup6->requestedVelocity = sensorGroup5.requestedVelocity;
		sensorGroup6->requestedRadius = sensorGroup5.requestedRadius;
		sensorGroup6->requestedRightWheelVelocity = sensorGroup5.requestedRightWheelVelocity;
		sensorGroup6->requestedLeftWheelVelocity = sensorGroup5.requestedLeftWheelVelocity;
	}

	return status;
}

int32_t irobotPrintSensorGroup6(
	const irobotSensorGroup6_t * const sensors
){	
	//catch NULL pointers
	if(!sensors){
		return ERROR_INVALID_PARAMETER;
	}

	printf("\n*********** iRobot Sensors ***********\n");
	printf(
		"Wheel Drops:\tCaster[%s] Left[%s] Right[%s]\n",
		sensors->bumps_wheelDrops.wheeldropCaster ? "X" : " ",
		sensors->bumps_wheelDrops.wheeldropLeft ? "X" : " ",
		sensors->bumps_wheelDrops.wheeldropRight ? "X" : " "
	);

	printf(
		"Bumps:\t\tLeft[%s] Right[%s]\n",
		sensors->bumps_wheelDrops.bumpLeft ? "X" : " ",
		sensors->bumps_wheelDrops.bumpRight ? "X" : " "
	);

	printf("Wall:\t\t[%s]\n", sensors->wall ? "X" : " ");

	printf(
		"Cliffs:\t\tLeft[%s] FrontLeft[%s] FrontRight[%s] Right[%s]\n",
		sensors->cliffLeft ? "X" : " ",
		sensors->cliffFrontLeft ? "X" : " ",
		sensors->cliffFrontRight ? "X" : " ",
		sensors->cliffRight ? "X" : " "
	);

	printf("Virtual Wall:\t[%s]\n", sensors->virtualWall ? "X" : " ");

	printf(
		"Overcurrent:\tLSD0[%s] LSD1[%s] LSD2[%s] LeftWheel[%s] RightWheel[%s]\n",
		sensors->lowSideDriver_WheelOvercurrent.lowSideDriver0 ? "X" : " ",
		sensors->lowSideDriver_WheelOvercurrent.lowSideDriver1 ? "X" : " ",
		sensors->lowSideDriver_WheelOvercurrent.lowSideDriver2 ? "X" : " ",
		sensors->lowSideDriver_WheelOvercurrent.leftWheel ? "X" : " ",
		sensors->lowSideDriver_WheelOvercurrent.rightWheel ? "X" : " "
	);

	printf("Infrared:\t0x%02X\n", sensors->infrared);

	printf(
		"Buttons:\tAdvance[%s] Play[%s]\n",
		sensors->buttons.advance ? "X" : " ",
		sensors->buttons.play ? "X" : " "
	);

	printf("Position:\tDistance[%d mm] Angle[%d deg]\n", sensors->distance, sensors->angle);

	printf("Charging State: ");
	switch(sensors->chargingState){
	case CHARGING_STATE_NOT_CHARGING:				printf("not charging\n");	break;
	case CHARGING_STATE_RECONDITION_CHARGING:		printf("reconditioning\n");	break;
	case CHARGING_STATE_FULL_CHARGING:				printf("full, charging\n");	break;
	case CHARGING_STATE_TRICKLE_CHARGING:			printf("trickle\n");		break;
	case CHARGING_STATE_WAITING:					printf("waiting\n");		break;
	case CHARGING_STATE_CHARGING_FAULT_CONDITION:	printf("fault\n");			break;
	default:										printf("unknown\n");		break;
	}

	printf(
		"Battery:\tVoltage[%d mV] Current[%d mA]\n",
		sensors->voltage,
		sensors->current
	);

	printf(
		"Battery:\tCharge[%d mAh] Capacity[%d mAh] Temp[%d C]\n",
		sensors->batteryCharge,
		sensors->batteryCapacity,
		sensors->batteryTemperature
	);

	printf("Wall Signal:\t%d\n", sensors->wallSignal);
	printf(
		"Cliff Signals:\tLeft[%d] FrontLeft[%d] FrontRight[%d] Right[%d]\n",
		sensors->cliffLeftSignal,
		sensors->cliffFrontLeftSignal,
		sensors->cliffFrontRightSignal,
		sensors->cliffRightSignal
	);

	printf(
		"Cargo DI:\tDI0[%s] DI1[%s] DI2[%s] DI3[%s] DeviceDetect[%s]\n",
		sensors->cargoBayDigitalInputs.digitalInput0 ? "X" : " ",
		sensors->cargoBayDigitalInputs.digitalInput1 ? "X" : " ",
		sensors->cargoBayDigitalInputs.digitalInput2 ? "X" : " ",
		sensors->cargoBayDigitalInputs.digitalInput3 ? "X" : " ",
		sensors->cargoBayDigitalInputs.deviceDetect ? "X" : " "
	);

	printf("Cargo Analog:\t%d\n", sensors->cargoBayAnalogSignal);

	printf(
		"Charge Sources:\tInternal[%s] Base[%s]\n",
		sensors->chargingSourcesAvailable.internalCharger ? "X" : " ",
		sensors->chargingSourcesAvailable.homeBase ? "X" : " "
	);

	printf("OI State:\t");
	switch(sensors->oiState){
	case OISTATE_OFF:		printf("OFF\n");	break;
	case OISTATE_PASSIVE:	printf("PASSIVE\n");break;
	case OISTATE_SAFE:		printf("SAFE\n");	break;
	case OISTATE_FULL:		printf("FULL\n");	break;
	default:				printf("UNKNOWN\n");break;
	}

	printf("Song:\t\tNumber[%d] Playing[%s]\n", sensors->songNumber, sensors->songPlaying ? "X" : " ");
	printf("Stream Packets:\t%d\n", sensors->nStreamPackets);
	printf("Requested:\tVelocity [%d] Radius[%d]\n", sensors->requestedVelocity, sensors->requestedRadius);
	printf("Requested:\tRight[%d] Left[%d]\n", sensors->requestedRightWheelVelocity, sensors->requestedLeftWheelVelocity);

	printf("*********** iRobot Sensors ***********\n");

	return ERROR_SUCCESS;
}
