/** \file irobotTime.h
 *
 * Abstraction layer for timing functions; architecture or OS-specific timing
 * functions are referenced here.
 *
 * \author Jeff C. Jensen
 * \date 2013-12-09
 * \copyright Copyright (C) 2013, Jeff C. Jensen, Edward A. Lee, and Sanjit A. Seshia.
 * 			  This software accompanies An Introductory Lab in Embedded and Cyber-Physical Systems
 * 			  and is licensed under a Creative Commons Attribution-NonCommercial-NoDerivs 3.0
 * 			  Unported License. See http://leeseshia.org/lab.
 */

#ifndef IROBOT_TIME_H
#define IROBOT_TIME_H

#include <stdint.h>

/// delay this process a fixed number of milliseconds
void irobotDelayMs(
	const int32_t ms	///< delay in ms
);


#endif /* IROBOT_TIME_H */
