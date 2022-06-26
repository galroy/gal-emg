/*
 * ledControl.c
 *
 *  Created on: Jun 16, 2022
 *      Author: student
 */
#include "ledControl.h"
//extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim4;

void ledInit(LED* led,GPIO_TypeDef* GPIOx,uint16_t GPIO_pin)
{
	if(led == NULL){
		return;
	}

	led->ledState = LED_OFF;
	led->GPIOx = GPIOx;
	led->GPIO_pin = GPIO_pin;
	led->brightness = 0;

}
void ledOn(LED* led){
	if(led == NULL){
		return;
	}
	led->ledState = LED_ON;
	HAL_GPIO_WritePin(led->GPIOx, led->GPIO_pin, 1);
}
void ledOff(LED* led){
	if(led == NULL){
		return;
	}
	led->ledState = LED_OFF;
	HAL_GPIO_WritePin(led->GPIOx, led->GPIO_pin, 0);
}
void setBrightness(LED* led,int brightness){
	led->brightness = brightness;
	//HAL_TIM_PWM_Start_IT(&htim4, TIM_CHANNEL_1);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, led->brightness*10);
}

