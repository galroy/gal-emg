/*
 * led.c
 *
 *  Created on: Jun 14, 2022
 *      Author: student
 */


#include "led.h"
extern TIM_HandleTypeDef htim6;
//LED ledR;
//LED ledB;
void ledInit(LED* led,GPIO_TypeDef* GPIOx,uint16_t GPIO_pin)
{
	if(led == NULL){
		return;
	}
	led->counter = 0;
	led->period = 0;
	led->ledState = LED_OFF;
	led->GPIOx = GPIOx;
	led->GPIO_pin = GPIO_pin;

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
void ledBlink(LED* led, int period){
	/*__HAL_TIM_SET_COUNTER(htim6,0);
	//__HAL_TIM_SET_AUTORELOAD(htim6,3000);
	__HAL_TIM_SET_AUTORELOAD(htim6,period);
	HAL_TIM_Base_Start_IT(htim6);*/
	led->ledState = LED_BLINK;
	led->period = period;
	led->counter = 0;

}
void ledOnTimerInterrupt(LED* led){
	if(led->ledState != LED_BLINK){
		return;
	}
	led->counter++;
	if(led->counter >= led->period){
		HAL_GPIO_TogglePin(led->GPIOx, led->GPIO_pin);
		led->counter = 0;
	}

}
void ledOnPeriodicTask(LED* led){

}
