/*
 * ledControl.h
 *
 *  Created on: Jun 16, 2022
 *      Author: student
 */

#ifndef INC_LEDCONTROL_H_
#define INC_LEDCONTROL_H_

#include "main.h"

typedef enum ledstate_{
	LED_ON,
	LED_OFF,
} LED_STATE;

typedef struct _led{
	LED_STATE ledState;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_pin;
	uint8_t brightness;
} LED;
void ledInit(LED* led,GPIO_TypeDef* GPIOx,uint16_t GPIO_pin);
void ledOn(LED* led);
void ledOff(LED* led);
void setBrightness(LED* led,int brightness);
#endif /* INC_LEDCONTROL_H_ */
