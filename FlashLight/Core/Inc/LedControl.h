/*
 * LedControl.h
 *
 *  Created on: Jun 9, 2022
 *      Author: student
 */

#ifndef INC_LEDCONTROL_H_
#define INC_LEDCONTROL_H_

#include "main.h"

typedef enum FlashLightState_
{
STATE_OFF,
STATE_ON,
STATE_WEAK,
STATE_FLICKERING

}FlashLightState;

typedef enum ButtonEvents_{
	BTN_UP,
	BTN_DOWN,
	BTN_SHOR,
	BTN_LONG,
	BTN_DCLICK
}ButtonEvents;

extern FlashLightState FlashState;
extern uint8_t brightness;
extern uint8_t counter;

extern ButtonEvents btnEvent;

FlashLightState state();
void ledON(TIM_HandleTypeDef* htim6);
void ledOFF(TIM_HandleTypeDef* htim6);
void ledWeak(TIM_HandleTypeDef* htim6);
void ledFlickering(TIM_HandleTypeDef* htim6);

void setBrightness(TIM_HandleTypeDef* htim6,int brightness);
#endif /* INC_LEDCONTROL_H_ */
