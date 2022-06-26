#include "RingBuffer_ADT.h"

#define INIT_VALUE 0x12345678

//#define RING_BUFFER_SIZE 8
//static int _head = 0;
//static int _tail = 0;
//static uint8_t _buffer[RING_BUFFER_SIZE];

// Initializes the ring buffer internal data structures
Result RingBuffer_Init(ringBufferObj* rb)
{
	if (rb == NULL)
	{
		return RESULT_INVALID_PARAMETER;
	}

	rb->head = rb->tail = 0;
	rb->initValue = INIT_VALUE;
	return RESULT_SUCCESS;
}

// returns 1 if it’s empty and 0 if it has at least one byte
int RingBuffer_IsEmpty(ringBufferObj* rb)
{
	return rb->head == rb->tail;
	//return _head == _tail;
}

// returns 1 if no more bytes can be added to the ring buffer
int RingBuffer_IsFull(ringBufferObj* rb)
{
	//return _tail == (_head) % RING_BUFFER_SIZE;
	return rb->tail = (rb->head) % RING_BUFFER_SIZE;
}

// returns the amount of free space in the buffer
int RingBuffer_FreeSpace(ringBufferObj* rb)
{
	int ret = 0;
	if (rb->head >= rb->tail) {
		ret = RING_BUFFER_SIZE - rb->head + rb->tail;
	}
	else {
		ret = rb->tail - rb->head;
	}
	return ret;
}

// Writes the data from the input array to the ring buffer.
// If it does not have enough space returns 0 and does not write any bytes,
// otherwise writes the bytes to the ring buffer and returns 1
Result RingBuffer_Write(ringBufferObj* rb,uint8_t * data, size_t dataSize)
{

	if ((int)dataSize > RingBuffer_FreeSpace(rb)) {
		return RESULT_RING_BUFFER_FULL;
	}


	while (dataSize--) {
		rb->buffer[rb->head] = *data++;
		if (rb->head < RING_BUFFER_SIZE) {
			rb->head++;
		}
		else {
			rb->head = 0;
		}
	}

	return RESULT_SUCCESS;
}

// Reads the amount of bytes specified in dataSize from the ring buffer to the data array
int RingBuffer_Read(ringBufferObj* rb,uint8_t* data, size_t dataSize)
{
	int readCount = 0;

	while (dataSize--) {
		*data++ = rb->buffer[rb->tail];
		rb->tail = (rb->tail + 1) % RING_BUFFER_SIZE;
		readCount++;
		//dataSize--;
	}
	if (rb->head == RING_BUFFER_SIZE) {
		rb->head = 0;
	}

	return readCount;
}

#ifdef _DEBUG
// prints the ring buffer.
void RingBuffer_DebugPrint(ringBufferObj* rb) {
	for (int i = 0; i < RING_BUFFER_SIZE; i++) {
		printf("buffer[%d] = %c\n", i, rb->buffer[i]);
	}
	printf("tail = %d head = %d\n", rb->tail, rb->head);
}
#endif // DEBUG
