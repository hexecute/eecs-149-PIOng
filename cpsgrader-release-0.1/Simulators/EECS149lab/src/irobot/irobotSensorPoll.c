#include "irobotOpcode.h"
#include "irobotSensor.h"
#include "irobotSensorPoll.h"
#include "xqueue.h"

int32_t irobotSensorPollSensorGroup6(
	const irobotUARTPort_t	port,
	irobotSensorGroup6_t *	const sensorGroup6
){
	int32_t status = ERROR_SUCCESS;

	// initialize communications buffer
	uint8_t txBuffer[OP_SENSORS_SIZE];
	uint8_t rxQueueBuffer[SENSOR_SIZE_UPPER_BOUND] = {0x00};
	xqueue_t rxQueue;
	xqueue_init(&rxQueue, rxQueueBuffer, SENSOR_SIZE_UPPER_BOUND);

	// check for NULL pointer
	if(!sensorGroup6){
		return ERROR_INVALID_PARAMETER;
	}

	// request packet
	txBuffer[0] = OP_SENSORS;
	txBuffer[1] = SENSOR_GROUP6;
	irobot_StatusMerge(&status, irobotUARTWriteRaw(port, txBuffer, OP_SENSORS_SIZE));
	
	// receive response
	if(!irobot_IsError(status)){
		irobot_StatusMerge(&status, irobotUARTRead(port, &rxQueue, SENSOR_GROUP6_SIZE));
	}

	// read response
	if(!irobot_IsError(status)){
		irobot_StatusMerge(&status, irobotReadSensorGroup6(&rxQueue, sensorGroup6));
	}

	return status;
}
