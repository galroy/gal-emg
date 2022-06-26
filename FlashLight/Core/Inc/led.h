/*
 * led.h
 *
 *  Created on: Jun 14, 2022
 *      Author: student
 */


#ifndef INC_LED_H_
#define INC_LED_H_
#include "main.h"

typedef enum ledstate_{
	LED_ON,
	LED_OFF,
	LED_BLINK
} LED_STATE;

typedef struct _led{
	LED_STATE ledState;
	int counter;
	int period;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_pin;
} LED;

void ledInit(LED* led,GPIO_TypeDef* GPIOx,uint16_t GPIO_pin);
void ledOn(LED* led);
void ledOff(LED* led);
void ledBlink(LED* led, int period);
void ledOnTimerInterrupt(LED* led);
void ledOnPeriodicTask(LED* led);

#endif /* INC_LED_H_ */
