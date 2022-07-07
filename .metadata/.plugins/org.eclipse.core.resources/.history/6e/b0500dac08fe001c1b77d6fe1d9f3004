/*
 * rtc.c
 *
 *  Created on: Jul 5, 2022
 *      Author: student
 */
#include "rtc.h"
#define PASS_ADRR 8

void initRTC(Rtc *rtc , I2C_HandleTypeDef* hi2c){
	rtc->hi2c = hi2c;
}

int setPass(Rtc *rtc,uint32_t pass){
	return HAL_I2C_Mem_Write(rtc->hi2c,0xD0,PASS_ADRR,1,(uint8_t *)&pass,sizeof(pass),0xFF);
}
int getPass(Rtc *rtc,uint32_t *pass){
	return HAL_I2C_Mem_Read(rtc->hi2c, 0xD0, PASS_ADRR, 1, (uint8_t *)pass, sizeof(*pass),0xFF);
}
