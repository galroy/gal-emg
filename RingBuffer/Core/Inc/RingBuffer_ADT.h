#ifndef _RING_BUFFER_H_
#define _RING_BUFFER_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define RING_BUFFER_SIZE 8

typedef enum
{
	RESULT_SUCCESS,

	RESULT_FAILD,

	RESULT_INVALID_PARAMETER,

	RESULT_RING_BUFFER_FULL,

	RESULT_OTHER_FAILURE

}Result;

typedef struct
{
	uint32_t initValue;
	int head;
	int tail;
	uint8_t buffer[RING_BUFFER_SIZE];


}ringBufferObj;



// Initializes the ring buffer internal data structures
Result RingBuffer_Init(ringBufferObj *rb);

// returns 1 if it’s empty and 0 if it has at least one byte
int RingBuffer_IsEmpty(ringBufferObj* rb);

// returns 1 if no more bytes can be added to the ring buffer
int RingBuffer_IsFull(ringBufferObj* rb);

// returns the amount of free space in the buffer
int RingBuffer_FreeSpace(ringBufferObj* rb);

// Writes the data from the input array to the ring buffer.
// If it does not have enough space returns 0 and does not write any bytes,
// otherwise writes the bytes to the ring buffer and returns 1
Result RingBuffer_Write(ringBufferObj* rb,uint8_t* data, size_t dataSize);

// Reads the amount of bytes specified in dataSize from the ring buffer to the data array
int RingBuffer_Read(ringBufferObj* rb,uint8_t* data, size_t dataSize);

// prints the ring buffer.
void RingBuffer_DebugPrint(ringBufferObj* rb);

#endif
