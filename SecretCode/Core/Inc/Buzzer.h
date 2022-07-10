/*
 * Buzzer.h
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include"main.h"

typedef enum BuzzerState_
{
	BUZ_STATE_OFF,
	BUZ_STATE_TONE,
	BUZ_STATE_MUSIC,
} BuzzerState;


typedef struct Buzzer_
{
	TIM_HandleTypeDef* pwmTimer;
	BuzzerState state;
	int counter;
	int maxCounter;
} Buzzer;

void buzzerInit(Buzzer * buzzer, TIM_HandleTypeDef* pwmTimer);
void buzzerOnTimerInterrupt(Buzzer * buzzer);
void buzzerPlayTone(Buzzer * buzzer, int frequency, int timeMS);
void buzzerStop(Buzzer * buzzer);

#endif /* BUZZER_H_ */
