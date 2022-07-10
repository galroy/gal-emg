/*
 * Led.h
 *
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include "main.h"
#include <stdint.h>

typedef enum LedState_
{
	STATE_OFF,
	STATE_ON,
	STATE_BLINK,
} LedState;

typedef struct Led_
{
	GPIO_TypeDef * gpioPort;
	uint16_t gpioPin;
	LedState state;
	int counter;
	int maxCounter;
} Led;

void ledInit(Led* led, GPIO_TypeDef* gpioPort, uint16_t gpioPin);
void ledOn(Led* led);
void ledOff(Led* led);
void ledBlink(Led* led, int period);
void ledOnTimerInterrupt(Led* led);


#endif /* INC_LED_H_ */
