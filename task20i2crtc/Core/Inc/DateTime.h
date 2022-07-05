/*
 * DateTime.h
 *
 *  Created on: Jun 30, 2022
 *      Author: student
 */

#ifndef INC_DATETIME_H_
#define INC_DATETIME_H_

#include <stdint.h>
#include "main.h"

typedef struct _Time{

	uint8_t year;
	uint8_t year10;
	uint8_t month;
	uint8_t month10;
	uint8_t date;
	uint8_t date10;
	uint8_t hour;
	uint8_t hour10;
	uint8_t minute;
	uint8_t minute10;
	uint8_t second;
	uint8_t second10;
} TIME;

typedef struct _clock{
	//TIME_STATE timeState;
	TIME time;
	I2C_HandleTypeDef *hi2c1;
	//TIM_HandleTypeDef *htim;
} CLOCK;

void clockInit(CLOCK *clk,TIME *tm,I2C_HandleTypeDef *hi2c1);
void I2CMemWrite(CLOCK *clk);
void printDateTime(CLOCK *clk);
uint8_t GetRight4BitNum(uint8_t num);
uint8_t GetLeft4BitNum(uint8_t num);
uint8_t dec2Bin(uint8_t dec);
int commTask(UART_HandleTypeDef *huart2);
uint8_t handleCommand(TIME *tm);
void led1On();
void led1Off();

void led2On();
void led2Off();

#endif /* INC_DATETIME_H_ */
