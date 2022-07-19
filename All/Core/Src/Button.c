/*
 * Button.c
 */

#include "Button.h"
#include "Led.h"
#include "main.h"
#include <stdio.h>

#define LONG_PRESS_MS 500
#define DOUBLE_PRESS_MS 500

void buttonInit(Button* button, GPIO_TypeDef* gpioPort, uint16_t gpioPin)
{
	button->gpioPort = gpioPort;
	button->gpioPin = gpioPin;
	button->pressTime = 0;
	button->state = BTN_PRESS_NONE;
	button->waitingForDouble = 0;
	button->counter = 0;
}

void buttonOnInterrupt(Button * button, uint16_t pin)
{
	if (pin == button->gpioPin) {
		if (HAL_GPIO_ReadPin(button->gpioPort, button->gpioPin) == 0) {
			button->pressTime = HAL_GetTick();
		}
		else {
			uint32_t releaseTime = HAL_GetTick();
			if (releaseTime - button->pressTime > LONG_PRESS_MS) {
				button->state = BTN_PRESS_LONG;
			}
			else {
				if (button->waitingForDouble) {
					button->state = BTN_PRESS_DOUBLE;
					button->waitingForDouble = 0;
				}
				else {
					button->state = BTN_PRESS_NONE;
					button->counter = 0;
					button->waitingForDouble = 1;
				}
			}
		}
	}
}

void buttonOnTimerInterrupt(Button * button)
{
	if (button->waitingForDouble != 0) {
		button->counter++;
		if (button->counter >= DOUBLE_PRESS_MS) {
			button->state = BTN_PRESS_SHORT;
			button->waitingForDouble = 0;
		}
	}
}

ButtonState buttonGetState(Button * button)
{
	ButtonState temp = button->state;
	button->state = BTN_PRESS_NONE;
	return temp;
}
