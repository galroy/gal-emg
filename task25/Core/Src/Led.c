/*
 * Led.c
 */

#include "Led.h"

void ledInit(Led* led, GPIO_TypeDef* gpioPort, uint16_t gpioPin)
{
	led->state = STATE_OFF;
	led->gpioPort = gpioPort;
	led->gpioPin = gpioPin;
	led->counter = 0;
	led->maxCounter = 0;
	led->ledon = ledOn;
	led->ledoff = ledOff;
	//led->pledon = ledOn2;
	//led->pledon3 = ledOn3;
	//led->this = led;

}
/*void RegisterCallbacks(HandlerFunc onFunc, HandlerFunc offFunc,void *obj){
	//staticLedOn = onFunc;
	//staticLedOff = offFunc;
	//ledon = ledOn1;
	//ledon(obj);
	//ledoff(obj);
}*/

/*void ledOn2(struct Led_* led){
	led->state = STATE_ON;
	HAL_GPIO_WritePin(led->gpioPort, led->gpioPin, 1);
}
void ledOn1(void* vled)
{
	Led *led = (Led*)vled;

	led->state = STATE_ON;
	HAL_GPIO_WritePin(led->gpioPort, led->gpioPin, 1);
}


void ledOff1(void* vled)
{
	Led *led = (Led*)vled;
	led->state = STATE_OFF;
	HAL_GPIO_WritePin(led->gpioPort, led->gpioPin, 0);
}*/

void ledOn(void* obj)
{
	Led *led = (Led*)obj;
	led->state = STATE_ON;
	HAL_GPIO_WritePin(led->gpioPort, led->gpioPin, 1);
}

void ledOff(void* obj)
{
	Led *led = (Led*)obj;
	led->state = STATE_OFF;
	HAL_GPIO_WritePin(led->gpioPort, led->gpioPin, 0);
}

void ledBlink(Led* led, int period)
{
	led->state = STATE_BLINK;
	led->counter = 0;
	led->maxCounter = period;
	HAL_GPIO_WritePin(led->gpioPort, led->gpioPin, 1);
}

void ledOnTimerInterrupt(Led* led)
{
	if (led->state == STATE_BLINK) {
		led->counter++;
		if (led->counter == led->maxCounter) {
			HAL_GPIO_TogglePin(led->gpioPort, led->gpioPin);
			led->counter = 0;
		}
	}
}
