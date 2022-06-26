/*
 * button.c
 *
 *  Created on: Jun 21, 2022
 *      Author: student
 */
#include "button.h"
#include "clock.h"
extern CLOCK mainClock;
#define LONG_PRESS_MS 500
#define WAIT_FOR_DOUBLE_PRESS 300


void buttonInit(BUTTON *btn,ButtonName btnName, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	if(btn == NULL){
		return;
	}
	btn->buttonState = BUTTON_STATE_NONE;
	btn->GPIOx = GPIOx;
	btn->GPIO_Pin = GPIO_Pin;
	btn->btnName = btnName;
	btn->pressTime = 0;
	btn->doublePressCounter = 0;
}
BUTTON_STATE getButtonState(BUTTON *btn){

	buttonDoublePressCountdown(btn);
	if(btn->buttonState == BUTTON_STATE_LONG_PRESS){
		return BUTTON_STATE_LONG_PRESS;
	}else{
		if(btn->buttonState == BUTTON_STATE_DOUBLE_PRESS){
			btn->doublePressCounter = 0;
			return btn->buttonState;
		}
		if(btn->buttonState == BUTTON_STATE_SHORT_PRESS && btn->doublePressCounter != 0){
			btn->buttonState = BUTTON_STATE_NONE;
		}else{
			btn->buttonState = BUTTON_STATE_SHORT_PRESS;
		}
	}
	return btn->buttonState;
}

void SetButtonNone(BUTTON *btn){
	if(btn != NULL){
		btn->buttonState = BUTTON_STATE_NONE;
	}
}

void buttonOnInterrupt(BUTTON *btn, uint16_t pin)
{

	if (pin == btn->GPIO_Pin) {
		if (HAL_GPIO_ReadPin(btn->GPIOx, btn->GPIO_Pin) == 0) {
			btn->pressTime = HAL_GetTick();
		}
		else {
			if ((HAL_GetTick() - btn->pressTime) > LONG_PRESS_MS) {
				btn->buttonState = BUTTON_STATE_LONG_PRESS;
			}
			else {
				if(btn->doublePressCounter != 0){
					btn->buttonState = BUTTON_STATE_DOUBLE_PRESS;
					btn->doublePressCounter = 0;
				}else{
					btn->buttonState = BUTTON_STATE_SHORT_PRESS;
					btn->doublePressCounter = WAIT_FOR_DOUBLE_PRESS;
				}


			}
		}
	}
	else{
		btn->buttonState = BUTTON_STATE_NONE;
	}
}

void buttonDoublePressCountdown(BUTTON *btn){
	if(btn->doublePressCounter > 0){
		btn->doublePressCounter--;
	}

}


