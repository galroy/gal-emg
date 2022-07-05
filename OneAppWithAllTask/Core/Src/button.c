/*
 * button.c
 *
 *  Created on: Jun 21, 2022
 *      Author: student
 */
#include "button.h"
#define LONG_PRESS_MS 500
#define DOUBLE_CLICK_MAX_TIME 300


void buttonInit(BUTTON *btn,ButtonName btnName, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	if(btn == NULL){
		return;
	}
	btn->buttonState = BUTTON_STATE_NONE;
	btn->GPIOx = GPIOx;
	btn->GPIO_Pin = GPIO_Pin;
	btn->btnName = btnName;
	btn->pressTime = 0;
	btn->countdown = 0;
}
BUTTON_STATE getButtonState(BUTTON *btn){
	/*if(btn->buttonState == BUTTON_STATE_WAIT_FOR_DOUBLE_CLICK && btn->countdown > 0){
		//btn->countdown--;

		//printf("%d\n\r",btn->countdown);
	}else{
		if(btn->buttonState == BUTTON_STATE_WAIT_FOR_DOUBLE_CLICK && btn->countdown == 0){
			btn->buttonState = BUTTON_STATE_SHORT_PRESS;
		}
	}*/
	if(btn->buttonState == BUTTON_STATE_WAIT_FOR_DOUBLE_CLICK && btn->countdown == 0){
				btn->buttonState = BUTTON_STATE_SHORT_PRESS;
	}

	return btn->buttonState;
}

void countdown(BUTTON *btn){
	if(btn->countdown > 0){
		btn->countdown--;
	}
}
void startDoubleClickCountdown(BUTTON *btn){
	btn->countdown = DOUBLE_CLICK_MAX_TIME;
}
void stopDoubleClickCountdown(BUTTON *btn){
	btn->countdown = 0;
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
			if (HAL_GetTick() - btn->pressTime > LONG_PRESS_MS) {
				btn->buttonState = BUTTON_STATE_LONG_PRESS;
			}
			else {

				//btn->buttonState = BUTTON_STATE_SHORT_PRESS;
				if(btn->buttonState != BUTTON_STATE_WAIT_FOR_DOUBLE_CLICK){
					btn->buttonState = BUTTON_STATE_WAIT_FOR_DOUBLE_CLICK;
					startDoubleClickCountdown(btn);
				}else{
					if(btn->buttonState == BUTTON_STATE_WAIT_FOR_DOUBLE_CLICK){
						btn->buttonState = BUTTON_STATE_DOUBLE_PRESS;
						stopDoubleClickCountdown(btn);
					}

				}



			}
		}
	}
	else{
		btn->buttonState = BUTTON_STATE_NONE;
	}
}



