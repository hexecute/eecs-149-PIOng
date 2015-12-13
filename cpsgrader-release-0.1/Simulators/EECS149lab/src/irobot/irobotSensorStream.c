#include "irobotSensor.h"
#include "irobotSensorStream.h"
#include "irobotOpcode.h"
#include "irobotError.h"
#include "irobotUART.h"

/// Upper-limit for the size of the OP_STREAM packet occurs when including all sensor IDs in a sensor packet
#define OP_SENSOR_STREAM_MAX_CODES	43
/// Maximum number of sensors, plus header and size bytes
#define OP_SENSOR_STREAM_MAX_SIZE	OP_SENSOR_STREAM_MAX_CODES + 2
/// header of a sensor stream packet
#define SENSOR_STREAM_HEADER		19

int32_t irobotSensorStreamConfigure(
	const irobotUARTPort_t			port,
	const irobotSensorCode * const	sensorCodes,
	uint8_t							nSensorCodes
){
	uint8_t packet[OP_SENSOR_STREAM_MAX_SIZE];
	uint8_t packetIndex = 0;
	uint8_t sensorCodeIndex = 0;

	// check for NULL pointers
	if(nSensorCodes && !sensorCodes){
		return ERROR_INVALID_PARAMETER;
	}

	nSensorCodes = nSensorCodes < OP_SENSOR_STREAM_MAX_CODES ? nSensorCodes : OP_SENSOR_STREAM_MAX_CODES;

	packet[packetIndex++] = OP_STREAM;
	packet[packetIndex++] = nSensorCodes;
	for(sensorCodeIndex = 0; sensorCodeIndex < nSensorCodes; sensorCodeIndex++){
		packet[packetIndex++] = sensorCodes[sensorCodeIndex];
	}

	return irobotUARTWriteRaw(port, packet, packetIndex);
}

int32_t irobotSensorStreamPause(
	const irobotUARTPort_t port,
	const bool pause
){
	uint8_t packet[OP_PAUSE_RESUME_STREAM_SIZE];

	packet[0] = OP_PAUSE_RESUME_STREAM;
	packet[1] = !pause;

	return irobotUARTWriteRaw(port, packet, OP_PAUSE_RESUME_STREAM_SIZE);
}

int32_t irobotSensorStreamStartAll(
	const irobotUARTPort_t			port
){
	int32_t status = ERROR_SUCCESS;
	const irobotSensorCode allSensors = SENSOR_GROUP6;

	irobot_IfIsNotError(status, irobotSensorStreamConfigure(port, &allSensors, 1));
	irobot_IfIsNotError(status, irobotSensorStreamPause(port, false));

	return status;
}

int32_t irobotSensorStreamProcessAll(
	xqueue_t * const queue,
	irobotSensorGroup6_t * const sensors,
	bool * const packetFound
){
	int32_t status = ERROR_SUCCESS;

	// check for NULL pointers
	if(!queue || !sensors || !packetFound){
		return ERROR_INVALID_PARAMETER;
	}

	*packetFound = false;

	//	Align buffer with iRobot sensor stream, according to format:
	//	[Header:19] [Len:27] [Packet ID:0] [SenGroup6 (52 bytes)] [CxSum]
	while(!xqueue_empty(queue) && xqueue_front(queue) != SENSOR_STREAM_HEADER){
		xqueue_drop(queue);
	}

	// Check for properly formatted header;
	//	NOTE: iRobot OI spec incorrectly omits the header from the checksum
	if( xqueue_count(queue) >= SENSOR_GROUP6_SIZE + 4	// size of entire packet		*/
	 && xqueue_pop(queue) == SENSOR_STREAM_HEADER		// sensor stream packet			*/
	 && xqueue_pop(queue) == SENSOR_GROUP6_SIZE + 1		// size of payload + checksum	*/
	 && xqueue_pop(queue) == SENSOR_GROUP6){			// payload is sensor group 6	*/
		 // Checksum: cxsum = [Header:19] + [n-bytes:Sen6Size+1=53] + [packet ID:6] + [data (Sen6Size)]
		 uint8_t cxsum = 0;
		 cxsum += SENSOR_STREAM_HEADER;
		 cxsum += SENSOR_GROUP6_SIZE + 1;
		 cxsum += SENSOR_GROUP6;
		 cxsum += xqueue_checksum(queue, SENSOR_GROUP6_SIZE + 1, 0);	// payload and encoded checksum

		 // checksum passed
		 if(cxsum == 0){
			 irobot_StatusMerge(&status, irobotReadSensorGroup6(queue, sensors));
			 xqueue_pop(queue);		// clear checksum
			 if(!irobot_IsError(status)){
				 *packetFound = true;
			 }
		 }
	}

	return status;
}
