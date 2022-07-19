/*
 * Button.h
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

typedef enum ButtonState_
{
	BTN_PRESS_NONE,
	BTN_PRESS_SHORT,
	BTN_PRESS_LONG,
	BTN_PRESS_DOUBLE,
} ButtonState;

typedef struct  Button_
{
	GPIO_TypeDef* gpioPort;
	uint16_t gpioPin;
	uint32_t pressTime;
	ButtonState state;
	int waitingForDouble;
	int counter;
} Button;

void buttonInit(Button* button, GPIO_TypeDef* gpioPort, uint16_t gpioPin);

void buttonOnInterrupt(Button * button, uint16_t pin);
void buttonOnTimerInterrupt(Button * button);
ButtonState buttonGetState(Button * button);

#endif /* INC_BUTTON_H_ */
