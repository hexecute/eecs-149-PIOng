#include "irobotError.h"

int32_t irobot_StatusMerge(
	int32_t * const status,
	const int32_t  newStatus
){
	if (!status){
		return ERROR_INVALID_PARAMETER;
	}
	else if(!irobot_IsError(*status)
		&& (*status == ERROR_SUCCESS || irobot_IsError(newStatus))
	){
		*status = newStatus;
	}

	return *status;
}
