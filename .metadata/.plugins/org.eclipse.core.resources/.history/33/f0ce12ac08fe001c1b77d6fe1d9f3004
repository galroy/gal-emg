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
} Rtc;

void initRTC(Rtc *rtc,I2C_HandleTypeDef* hi2c);
int setPass(Rtc *rtc,uint32_t pass);
int getPass(Rtc *rtc,uint32_t *pass);
#endif /* INC_RTC_H_ */
