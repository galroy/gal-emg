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

typedef void (*led_ptr)(void*);
//typedef void (*ledoff_ptr)(void*);
//typedef void (*ledon3_ptr)();
//typedef void (*HandlerFunc)(void*);
//typedef void (*HandlerFunc)();

typedef struct Led_
{
	GPIO_TypeDef * gpioPort;
	uint16_t gpioPin;
	LedState state;
	int counter;
	int maxCounter;
	//void (*ledon_ptr)(Led*);
	led_ptr ledon;
	led_ptr ledoff;
	//ledon3_ptr ledon3;
	//void (*pledon)(struct Led_ *self);

	//struct Led_ *this;
	//HandlerFunc handl;
} Led;
//static led_ptr ledon;
//static led_ptr ledoff;
//static HandlerFunc staticLedOn;
//static HandlerFunc staticLedOff;
//void ledOn1(Led* led);
void ledInit(Led* led, GPIO_TypeDef* gpioPort, uint16_t gpioPin);
//void ledOn3();
//void ledOn2(struct Led_* led);
//void ledOn1(void* vled);
void ledOn(void* obj);
void ledOff(void* obj);
//void ledOff1(void* vled);
void ledBlink(Led* led, int period);
void ledOnTimerInterrupt(Led* led);
//void RegisterCallbacks(HandlerFunc onFunc, HandlerFunc offFunc,void *obj);


#endif /* INC_LED_H_ */
