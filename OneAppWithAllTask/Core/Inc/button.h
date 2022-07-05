/*
 * button.h
 *
 *  Created on: Jun 21, 2022
 *      Author: student
 */

#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_

#include "MyMain.h"

typedef enum buttontate_{
	BUTTON_STATE_NONE,
	BUTTON_STATE_SHORT_PRESS,
	BUTTON_STATE_LONG_PRESS,
	BUTTON_STATE_DOUBLE_PRESS,
	BUTTON_STATE_WAIT_FOR_DOUBLE_CLICK
} BUTTON_STATE;

typedef enum ButtonName_
{
	BTN_SW1,
	BTN_SW2
} ButtonName;


typedef struct _button{
	BUTTON_STATE buttonState;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	ButtonName btnName;
	uint32_t pressTime;
	uint32_t countdown;
} BUTTON;

void buttonInit(BUTTON *btn,ButtonName btnName, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
BUTTON_STATE getButtonState(BUTTON *btn);
void SetButtonNone(BUTTON *btn);
void buttonOnInterrupt(BUTTON *btn, uint16_t pin);
void startDoubleClickCountdown(BUTTON *btn);
void stopDoubleClickCountdown(BUTTON *btn);
void countdown(BUTTON *btn);


/*typedef enum
{
    NO_PRESS,
    SINGLE_PRESS,
    LONG_PRESS,
    DOUBLE_PRESS,
	WAIT_FOR_DOUBLE_CLICK
} eButtonEvent ;

uint8_t buttonState(BUTTON *btn);
eButtonEvent getButtonEvent(BUTTON *btn);*/


#endif /* SRC_BUTTON_H_ */
