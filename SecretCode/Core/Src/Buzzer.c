/*
 * Buzzer.c
 */


#include "Buzzer.h"

const int NotesFreqs[] = {
		0, // Pause
		262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, // 1st octave frequencies
		523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988  // 2nd octave frequencies
};


void buzzerInit(Buzzer * buzzer, TIM_HandleTypeDef* pwmTimer)
{
	HAL_NVIC_EnableIRQ(TIM3_IRQn);
	buzzer->pwmTimer = pwmTimer;
	buzzer->state = BUZ_STATE_OFF;
	buzzer->counter = 0;
	buzzer->maxCounter = 0;
}

void buzzerOnTimerInterrupt(Buzzer * buzzer)
{
	if (buzzer->state == BUZ_STATE_TONE) {

		buzzer->counter++;
		if (buzzer->counter >= buzzer->maxCounter) {
			buzzerStop(buzzer);
			buzzer->counter = 0;
		}
	}
}

void buzzerStop(Buzzer * buzzer)
{
	buzzer->state = BUZ_STATE_OFF;

	HAL_TIM_Base_Stop(buzzer->pwmTimer);
	HAL_TIM_PWM_Stop(buzzer->pwmTimer, TIM_CHANNEL_1);
}

void buzzerPlayTone(Buzzer * buzzer, int frequency, int timeMs)
{
	buzzer->state = BUZ_STATE_TONE;

	int per = (100000 + frequency / 2) / frequency;
	__HAL_TIM_SET_COUNTER(buzzer->pwmTimer, 0);
	__HAL_TIM_SET_AUTORELOAD(buzzer->pwmTimer, per);
	__HAL_TIM_SET_COMPARE(buzzer->pwmTimer, TIM_CHANNEL_1, (per /2));

	HAL_TIM_PWM_Start(buzzer->pwmTimer, TIM_CHANNEL_1);
	HAL_TIM_Base_Start(buzzer->pwmTimer);

	buzzer->counter = 0;
	buzzer->maxCounter = timeMs;
}
