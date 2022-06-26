/*
 * ringBuffer.c
 *
 *  Created on: May 31, 2022
 *      Author: student
 */
#include "ringBuffer.h"

uint8_t g_arrRingBuffer[BUFFER_SIZE];
int g_head = 0;
int g_tail = 0;

//initializes the ring buffer internal data structures
void RingBuffer_Init(){
	g_head = 0;
	g_tail = 0;
}

//returns 1 if it’s empty and 0 if it has at least one byte
int RingBuffer_IsEmpty(){
	if(BUFFER_SIZE - (g_head -g_tail) == 0){
		return 1;
	}
	return 0;
}

//returns 1 if no more bytes can be added to the ring buffer
int RingBuffer_IsFull(){
	if((g_head - g_tail) == BUFFER_SIZE){
			return 1;
		}
	return 0;
}

//returns the amount of free space in the buffer
int RingBuffer_FreeSpace(){
	return (BUFFER_SIZE -(g_tail - g_head));
}


//writes the data from the input array to the ring buffer.
//If it does not have enough space returns 0 and does not write any bytes,
//otherwise writes the bytes to the ring buffer and returns 1
int RingBuffer_Write(uint8_t * data, size_t dataSize){
	if(dataSize > RingBuffer_FreeSpace()){
		return 0;
	}
	for(size_t i = 0; i < dataSize; i++){
		g_arrRingBuffer[g_tail] = *data;
		data++;
		g_tail++;
	}
	g_tail++;
	return 1;
}

//reads the amount of bytes specified in dataSize from the ring buffer to the data array.
int RingBuffer_Read(uint8_t * data, size_t dataSize){
	if(dataSize > BUFFER_SIZE){
		dataSize = BUFFER_SIZE;
	}
	size_t i = 0;
	for(i = 0; i<dataSize; i++){
		data[i] = g_arrRingBuffer[g_head];
		g_head++;
	}

	return i;
}

