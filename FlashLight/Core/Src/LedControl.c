/*
 * LedControl.c
 *
 *  Created on: Jun 9, 2022
 *      Author: student
 */
#include "LedControl.h"

FlashLightState FlashState = STATE_OFF;
uint8_t brightness = 0;
uint8_t counter = 0;

//extern TIM_HandleTypeDef htim6;
ButtonEvents btnEvent = BTN_UP;


FlashLightState state(){
	switch(FlashState){
	case STATE_OFF:
		FlashState = STATE_ON;
		break;
	case STATE_ON:
			FlashState = STATE_WEAK;
			break;
	case STATE_WEAK:
			FlashState = STATE_FLICKERING;
			break;
	case STATE_FLICKERING:
				FlashState = STATE_OFF;
				break;

	}
	return FlashState;
}

void ledON(TIM_HandleTypeDef* htim6){
	HAL_TIM_Base_Stop_IT(htim6);
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);
}

void ledOFF(TIM_HandleTypeDef* htim6){
	HAL_TIM_Base_Stop_IT(htim6);
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0);
}

void ledWeak(TIM_HandleTypeDef* htim6){
	__HAL_TIM_SET_COUNTER(htim6,0);
	__HAL_TIM_SET_AUTORELOAD(htim6,100);
	HAL_TIM_Base_Start_IT(htim6);
}
void ledFlickering(TIM_HandleTypeDef* htim6){
	__HAL_TIM_SET_COUNTER(htim6,0);
	__HAL_TIM_SET_AUTORELOAD(htim6,3000);
	HAL_TIM_Base_Start_IT(htim6);
}

void setBrightness(TIM_HandleTypeDef* htim6,int bright){
	counter = 0;
	brightness = bright;
	__HAL_TIM_SET_COUNTER(htim6,0);
	__HAL_TIM_SET_AUTORELOAD(htim6,10);

	HAL_TIM_Base_Start_IT(htim6);

	/*__HAL_TIM_SET_COUNTER(htim6,0);
	__HAL_TIM_SET_AUTORELOAD(htim6,5);*/
}




