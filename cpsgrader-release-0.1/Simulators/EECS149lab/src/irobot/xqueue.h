/** \file xqueue.h
 * 
 * Definition and prototypes for xqueue data structure. xqueue is designed for use
 * in communication systems and concurrent environments where two processes may
 * access the queue, though exclusively one will read and one will write. Read and
 * write counts are tracked separately for this reason.
 * 
 * xqueues are initialized with the address of a buffer and its size, which must
 * be a power of two. This is to allow for simple circular access to the buffer
 * via masking, instead using a costly modulo operator.
 *
 * \author Jeff C. Jensen
 * \date 2013-12-09
 * \copyright Copyright (C) 2013, Jeff C. Jensen, Edward A. Lee, and Sanjit A. Seshia.
 * 			  This software accompanies An Introductory Lab in Embedded and Cyber-Physical Systems
 * 			  and is licensed under a Creative Commons Attribution-NonCommercial-NoDerivs 3.0
 * 			  Unported License. See http://leeseshia.org/lab.
 */

#ifndef _XQUEUE_H
#define _XQUEUE_H

#include "irobotTypes.h"

/// xqueue_t structure: queue with arbitrary length.
/// Separation of write/read count allows for use in concurrent environments
typedef struct{
	uint8_t		*data;				///< Assigned on initialization to existing buffer
	size_t		head;				///< Buffer write index
	size_t		tail;				///< Buffer read index
	size_t		rCount;				///< Read count
	size_t		wCount;				///< Write count
	size_t		capacity;			///< Maximum size of the data buffer (must be a power of 2, <= 0x8000)
	size_t		capacityMask;		///< Mask used instead of costly modulo operator
} xqueue_t;

/// Initialize a queue
void xqueue_init(
	xqueue_t * const queue,			///< [out]	Queue struct to initialize
	uint8_t * const dataBuffer,		///< [out]	Raw buffer to which queue will attach
	const size_t size				///< [in]	Size of the raw buffer
);

/// Number of used elements in the queue
/// \return number of elements in the queue
size_t xqueue_count(
	const xqueue_t * const queue	///< [in]	Target queue
);

/// Whether or not the queue is empty
/// \return Queue is empty?
bool xqueue_empty(
	const xqueue_t * const queue	///< [in]	Target queue
);

/// Whether or not the queue is full
/// \return Queue is full?
bool xqueue_full(
	const xqueue_t * const queue	///< [in]	Target queue
);

/// Number of free elements in the queue
/// \return number of free elements in the queue
size_t xqueue_space(
	const xqueue_t * const queue	///< [in]	Target queue
);

/// Front element of the queue
/// \return Front element of the queue
uint8_t xqueue_front(
	const xqueue_t * const queue	///< [in]	Target queue
);

/// Return the back (most recently added) element of the queue
/// \return Back element of the queue
uint8_t xqueue_back(
	const xqueue_t * const queue	///< [in]	Target queue
);

/// Index an element of the queue
/// \return Indexed element of the queue
uint8_t xqueue_at(
	const xqueue_t * const queue,	///< [in]	Target queue
	const size_t index				///< [in]	Element index
);

/// Clears a queue; retains buffer address and maximum size
void xqueue_clear(
	xqueue_t * const queue			///< [in/out]	Target queue
);

/// Push a single element on to a queue
/// \return Value pushed
uint8_t xqueue_push(
	xqueue_t * const queue,			///< [in/out]	Target queue
	const uint8_t value				///< [in]	byte to add to queue
);

/// Push 8 bits (one element) to a queue
#define xqueue_push8 xqueue_push

/// Push a 16-bit number to the queue (2 elements)
void xqueue_push16(
	xqueue_t * const queue,			///< [in/out]	Target queue
	const uint16_t value			///< [in]	Element to push
);

/// Push a 32-bit number to the queue (4 elements)
void xqueue_push32(
	xqueue_t * const queue,			///< [in/out]	Target queue
	const uint32_t value			///< [in]	Element to push
);

/// Push a stream on to a queue (faster than push_string)
void xqueue_push_buffer(
	xqueue_t * const queue,			///< [in/out]	Target queue
	const uint8_t * values,			///< [in]	Stream to push to queue
	const size_t nvalues			///< [in]	Number of elements to push
);

/// Push a (null-terminated) string on to a queue
void xqueue_push_string(
	xqueue_t * const queue,			///< [in/out]	Target queue
	const unsigned char * str		///< [in]	String to push to queue (NULL element is not pushed)
);

/// Pop an element from a queue
/// \return Front (removed) element of the queue
uint8_t xqueue_pop(
	xqueue_t * const queue			///< [in/out]	Target queue
);

/// Pop an 8-bit value from a queue
#define xqueue_pop8	xqueue_pop

/// Pop 16 bits (two elements) from a queue
/// \return Packed 16-bit integer containing front two (removed) elements of the queue.
uint16_t xqueue_pop16(
	xqueue_t * const queue			///< [in/out]	Target queue
);

/// Pop 32 bits (four elements) from a queue
/// \return Packed 32-bit integer containing front four (removed) elements of the queue.
uint32_t xqueue_pop32(
	xqueue_t * const queue			///< [in/out]	Target queue
);

/// Pop a sequence of elements from a queue
void xqueue_pop_buffer(
	xqueue_t * const queue,			///< [in/out]	Target queue
	uint8_t * values,				///< [out]	Stream to fill with values
	const size_t nvalues			///< [in]	Number of elements to pop
);

/// Pop an element from a queue; do not return value (fast)
void xqueue_drop(
	xqueue_t * const queue			///< [in/out]	Target queue
);

/// Pop many elements from a queue (fast)
void xqueue_drop_many(
	xqueue_t * const queue,			///< [in/out]	Target queue
	size_t nvalues					///< [in]	Number of elements to pop
);

/// Checksum of n elements currently in the queue
/// \returns 8-bit checksum of n front elements of the queue, queue[fromCount] to queue[fromCount + nvalues]
uint8_t xqueue_checksum(
	const xqueue_t * const queue,	///< [in]	Target queue
	size_t nvalues,					///< [in]	Number of values over which to sum
	const size_t nAdvance			///< [in]	Number of elements to advance before calculating checksum
);


#endif	// _XQUEUE_H
