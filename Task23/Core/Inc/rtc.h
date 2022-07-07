/*
 * rtc.h
 *
 *  Created on: Jul 5, 2022
 *      Author: student
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_

#include <stdint.h>
#include "main.h"


typedef struct _rtc{
	I2C_HandleTypeDef *hi2c;
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t day;
	uint8_t month;
	uint8_t year;
} Rtc;

void initRTC(Rtc *rtc,I2C_HandleTypeDef* hi2c);
int setPass(Rtc *rtc,uint32_t pass);
int getPass(Rtc *rtc,uint32_t *pass);
int setTimeToUlock(Rtc *rtc,uint8_t *timeToUnLock);
int getTimeToUlock(Rtc *rtc,uint8_t *timeToUnLock);
void SetClockTo01_01_00(Rtc *rtc);
uint8_t getSecFrom01_01_00(Rtc *rtc);
#endif /* INC_RTC_H_ */
