/** \file irobotError.h
 *
 * iRobot error handling and codes.
 *
 * \author Jeff C. Jensen
 * \date 2013-12-09
 * \copyright Copyright (C) 2013, Jeff C. Jensen, Edward A. Lee, and Sanjit A. Seshia.
 * 			  This software accompanies An Introductory Lab in Embedded and Cyber-Physical Systems
 * 			  and is licensed under a Creative Commons Attribution-NonCommercial-NoDerivs 3.0
 * 			  Unported License. See http://leeseshia.org/lab.
 */

#ifndef _IROBOTERROR_H
#define _IROBOTERROR_H

#include "irobotTypes.h"

#ifndef ERROR_SUCCESS
/// Operation successful
#define ERROR_SUCCESS				0
#endif

#ifndef ERROR_INVALID_PARAMETER
/// Operation received an invalid parameter
#define ERROR_INVALID_PARAMETER		-52005
#endif

#ifndef ERROR_TIMEOUT
/// Operation timed out
#define ERROR_TIMEOUT				-50400
#endif


/**
 * Tests whether a status is an error.
 *
 * @param status status to check for an error
 * @return whether the status was an error
 */
#define irobot_IsError(status)	((status) < ERROR_SUCCESS)

/**
 * Conditionally sets the status to a new value. The previous status is
 * preserved unless the new status is more of an error, which means that
 * warnings and errors overwrite successes, and errors overwrite warnings. New
 * errors do not overwrite older errors, and new warnings do not overwrite
 * older warnings.
 *
 * @param status status to conditionally set
 * @param newStatus new status value that may be set
 * @return the resulting status
 */
int32_t irobot_StatusMerge(int32_t * const status, const int32_t newStatus);

/**
 * This macro evaluates the expression only if the status is not an error. The
 * expression must evaluate to a int32_t, because the status will be set to the
 * returned status if the expression is evaluated.
 *
 * You can use this macro to mimic status chaining:
 *
 *    int32_t status = ERROR_SUCCESS;
 *    IfIsNotError(&status, SendMessage(...));
 *    IfIsNotError(&status, SendMessage(...));
 *    IfIsNotError(&status, SendMessage(...));
 *
 * @param status status to check for an error
 * @param expression expression to call if the incoming status is not an error
 */
#define irobot_IfIsNotError(status, expression) \
   if(!irobot_IsError(status)) \
   { \
	   irobot_StatusMerge(&status, (expression)); \
   }


#endif // _IROBOTERROR_H
