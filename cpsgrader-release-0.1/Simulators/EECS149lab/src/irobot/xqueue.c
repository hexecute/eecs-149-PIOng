#include "xqueue.h"

#ifndef MIN
	#define MIN(x,y) ( (x) < (y) ? (x) : (y) )
#endif

void xqueue_init(xqueue_t * const queue, uint8_t * const dataBuffer, const size_t size){
	queue->capacity = size;
	queue->capacityMask = size-1;
	queue->data = dataBuffer;
	queue->rCount = 0;
	queue->wCount = 0;
	queue->head = 0;
	queue->tail = 0;
}

size_t xqueue_count(const xqueue_t * const queue){
	return queue->wCount - queue->rCount;
}

bool xqueue_empty(const xqueue_t * const queue){
	return queue->wCount == queue->rCount;
}

bool xqueue_full(const xqueue_t * const queue){
	return xqueue_count(queue) >= queue->capacity;
}

size_t xqueue_space(const xqueue_t * const queue){
	return queue->capacity - xqueue_count(queue);
}

uint8_t xqueue_front(const xqueue_t * const queue){
	return queue->data[queue->tail];
}

uint8_t xqueue_back(const xqueue_t * const queue){
	return queue->data[(queue->head - 1) & queue->capacityMask];
}

uint8_t xqueue_at(const xqueue_t * const queue, const size_t index){
	return queue->data[(queue->tail + index) & queue->capacityMask];
}

void xqueue_clear(xqueue_t * const queue){
	queue->rCount = 0;
	queue->wCount = 0;
	queue->head = 0;
	queue->tail = 0;
}

uint8_t xqueue_push(xqueue_t * const queue, const uint8_t value){
	if(xqueue_full(queue))
		xqueue_drop(queue);

	*(queue->data + queue->head) = value;
	queue->head = (queue->head + 1) & queue->capacityMask;
	queue->wCount++;
	return value;
}

void xqueue_push16(xqueue_t * const queue, const uint16_t value){
	xqueue_push8(queue, HO(value));
	xqueue_push8(queue, LO(value));
}

void xqueue_push32(xqueue_t * const queue, const uint32_t value){
	xqueue_push8(queue, HHO(value));
	xqueue_push8(queue, HLO(value));
	xqueue_push8(queue, LHO(value));
	xqueue_push8(queue, LLO(value));
}

void xqueue_push_buffer(xqueue_t * const queue, const uint8_t * values, const size_t nvalues){
	size_t ii;
	if(nvalues >= queue->capacity)
		return;
	else if(nvalues > xqueue_space(queue))
		xqueue_drop_many(queue, nvalues - xqueue_space(queue));
	
	for(ii = 0; ii < nvalues; ii++){
		*(queue->data + queue->head) = *values++;
		queue->head = (queue->head + 1) & queue->capacityMask;
	}
	queue->wCount += ii;
}

void xqueue_push_string(xqueue_t * const queue, const unsigned char * str){
	size_t ii;
	for(ii = 0; *str; ii++){
		if(xqueue_full(queue))
			xqueue_drop(queue);
		*(queue->data + queue->head) = *str++;
		queue->head = (queue->head + 1) & queue->capacityMask;
		queue->wCount++;
	}
}

uint8_t xqueue_pop(xqueue_t * const queue){
	uint8_t value = *(queue->data + queue->tail);
	queue->tail = (queue->tail + 1) & queue->capacityMask;
	queue->rCount++;
	return value;
}

uint16_t xqueue_pop16(xqueue_t * const queue){
	return MHO(xqueue_pop8(queue)) | MLO(xqueue_pop8(queue));
}

uint32_t xqueue_pop32(xqueue_t * const queue){
	return MHHO(xqueue_pop8(queue)) | MHLO(xqueue_pop8(queue)) | MLHO(xqueue_pop8(queue)) | MLLO(xqueue_pop8(queue));
}

void xqueue_pop_buffer(xqueue_t * const queue,	uint8_t * values, const size_t nvalues){
	size_t ii;
	for(ii = 0; ii < nvalues && !xqueue_empty(queue); ii++){
		*values++ = *(queue->data + queue->tail);
		queue->tail = (queue->tail + 1) & queue->capacityMask;
		queue->rCount++;
	}
}

void xqueue_drop(xqueue_t * const queue){
	queue->tail = (queue->tail + 1) & queue->capacityMask;
	queue->rCount++;
}

void xqueue_drop_many(xqueue_t * const queue, size_t n){
	n = MIN(n, xqueue_count(queue));

	queue->tail = (queue->tail + n) & queue->capacityMask;
	queue->rCount += n;
}

uint8_t xqueue_checksum(const xqueue_t * const queue, size_t nvalues, const size_t nAdvance){
	uint8_t cxsum = 0;
	size_t ii;
	nvalues = MIN(nvalues, xqueue_count(queue) - nAdvance);
	for(ii = 0; ii < nvalues; ii++){
		cxsum += xqueue_at(queue, ii + nAdvance);
	}
	return cxsum;
}
