/*
 * buzzer.c
 *
 *  Created on: Jul 5, 2022
 *      Author: student
 */
#include "Buzzer.h"

enum Notes_
{
	NOTE_PAUSE,
	NOTE_1_C,
	NOTE_1_C_SH,
	NOTE_1_D,
	NOTE_1_D_SH,
	NOTE_1_E,
	NOTE_1_F,
	NOTE_1_F_SH,
	NOTE_1_G,
	NOTE_1_G_SH,
	NOTE_1_A,
	NOTE_1_A_SH,
	NOTE_1_B,
	NOTE_2_C,
	NOTE_2_C_SH,
	NOTE_2_D,
	NOTE_2_D_SH,
	NOTE_2_E,
	NOTE_2_F,
	NOTE_2_F_SH,
	NOTE_2_G,
	NOTE_2_G_SH,
	NOTE_2_A,
	NOTE_2_A_SH,
	NOTE_2_B,
};

enum Lengths_
{
	LEN_1,
	LEN_2,
	LEN_4,
	LEN_8,
	LEN_16
};

const int NotesFreqs[] = {
		0, // Pause
		262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, // 1st octave frequencies
		523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988  // 2nd octave frequencies
};

// Star Wars Main theme - notes and lengths
const int Notes[] = {
		NOTE_1_D, NOTE_1_D, NOTE_1_D,
		NOTE_1_G, NOTE_2_D,
		NOTE_2_C, NOTE_1_B, NOTE_1_A, NOTE_2_G, NOTE_2_D,
		NOTE_2_C, NOTE_1_B, NOTE_1_A, NOTE_2_G, NOTE_2_D,
		NOTE_2_C, NOTE_1_B, NOTE_2_C, NOTE_1_A, NOTE_PAUSE, NOTE_1_D, NOTE_1_D,
		NOTE_1_G, NOTE_2_D,
		NOTE_2_C, NOTE_1_B, NOTE_1_A, NOTE_2_G, NOTE_2_D,
		NOTE_2_C, NOTE_1_B, NOTE_1_A, NOTE_2_G, NOTE_2_D,
		NOTE_2_C, NOTE_1_B, NOTE_2_C, NOTE_1_A, NOTE_PAUSE, NOTE_1_D, NOTE_1_D,
		NOTE_1_E, NOTE_1_E, NOTE_1_E, NOTE_2_C, NOTE_1_B, NOTE_1_A, NOTE_1_G,
		NOTE_1_G, NOTE_1_A, NOTE_1_B, NOTE_1_A, NOTE_1_E, NOTE_1_F_SH, NOTE_1_D, NOTE_1_D,
		NOTE_1_E, NOTE_1_E, NOTE_1_E, NOTE_2_C, NOTE_1_B, NOTE_1_A, NOTE_1_G,
		NOTE_2_D, NOTE_1_A, NOTE_1_D, NOTE_1_D,
		NOTE_1_E, NOTE_1_E, NOTE_1_E, NOTE_2_C, NOTE_1_B, NOTE_1_A, NOTE_1_G,
		NOTE_1_G, NOTE_1_A, NOTE_1_B, NOTE_1_A, NOTE_1_E, NOTE_1_F_SH, NOTE_2_D, NOTE_2_D,
		NOTE_2_G, NOTE_2_G, NOTE_2_F, NOTE_2_D_SH, NOTE_2_D_SH, NOTE_2_D, NOTE_2_C, NOTE_2_C, NOTE_1_A_SH, NOTE_1_A, NOTE_1_A, NOTE_1_G,
		NOTE_2_D, NOTE_2_D, NOTE_1_D, NOTE_1_D, NOTE_1_D,
		NOTE_1_G, NOTE_2_D,
		NOTE_2_C, NOTE_1_B, NOTE_1_A, NOTE_2_G, NOTE_2_D,
		NOTE_2_C, NOTE_1_B, NOTE_1_A, NOTE_2_G, NOTE_2_D,
		NOTE_2_C, NOTE_1_B, NOTE_2_C, NOTE_1_A, NOTE_PAUSE, NOTE_1_D, NOTE_1_D,
		NOTE_1_G, NOTE_2_D,
		NOTE_2_C, NOTE_1_B, NOTE_1_A, NOTE_2_G, NOTE_2_D,
		NOTE_2_C, NOTE_1_B, NOTE_1_A, NOTE_2_G, NOTE_1_G, NOTE_1_G, NOTE_1_G, NOTE_1_G,
};
const int Lengths[] = {
		LEN_8, LEN_8, LEN_8,
		LEN_2, LEN_2,
		LEN_8, LEN_8, LEN_8, LEN_2, LEN_4,
		LEN_8, LEN_8, LEN_8, LEN_2, LEN_4,
		LEN_8, LEN_8, LEN_8, LEN_4, LEN_16, LEN_8, LEN_8,
		LEN_2, LEN_2,
		LEN_8, LEN_8, LEN_8, LEN_2, LEN_4,
		LEN_8, LEN_8, LEN_8, LEN_2, LEN_4,
		LEN_8, LEN_8, LEN_8, LEN_4, LEN_16, LEN_8, LEN_8,
		LEN_4, LEN_8, LEN_8, LEN_8, LEN_8, LEN_8, LEN_8,
		LEN_8, LEN_8, LEN_8, LEN_8, LEN_8, LEN_4, LEN_8, LEN_8,
		LEN_4, LEN_8, LEN_8, LEN_8, LEN_8, LEN_8, LEN_8,
		LEN_4, LEN_2, LEN_8, LEN_8,
		LEN_4, LEN_8, LEN_8, LEN_8, LEN_8, LEN_8, LEN_8,
		LEN_8, LEN_8, LEN_8, LEN_8, LEN_8, LEN_4, LEN_8, LEN_8,
		LEN_8, LEN_16, LEN_16, LEN_8, LEN_16, LEN_16, LEN_8, LEN_16, LEN_16, LEN_8, LEN_16, LEN_16,
		LEN_2, LEN_4, LEN_8, LEN_8, LEN_8,
		LEN_2, LEN_2,
		LEN_8, LEN_8, LEN_8, LEN_2, LEN_4,
		LEN_8, LEN_8, LEN_8, LEN_2, LEN_4,
		LEN_8, LEN_8, LEN_8, LEN_4, LEN_16, LEN_8, LEN_8,
		LEN_2, LEN_2,
		LEN_8, LEN_8, LEN_8, LEN_2, LEN_4,
		LEN_8, LEN_8, LEN_8, LEN_4, LEN_8, LEN_8, LEN_8, LEN_4,
};

const int FullLen = 1600;

void buzzerInit(Buzzer * buzzer, TIM_HandleTypeDef* pwmTimer)
{
	HAL_NVIC_EnableIRQ(TIM3_IRQn);
	buzzer->pwmTimer = pwmTimer;
	buzzer->state = BUZ_STATE_OFF;
	buzzer->counter = 0;
	buzzer->maxCounter = 0;
	buzzer->noteIdx = 0;
	buzzer->notesCount = sizeof(Notes) / sizeof(Notes[0]);
	buzzer->noteFreqs = Notes;
	buzzer->noteLengths = Lengths;
}

void buzzerOnTimerInterrupt(Buzzer * buzzer)
{
	if (buzzer->state != BUZ_STATE_MUSIC) {
		return;
	}

	if (buzzer->counter >= buzzer->maxCounter) {
		if (buzzer->noteFreqs[buzzer->noteIdx] != NOTE_PAUSE)
		{
			int freq = (NotesFreqs[buzzer->noteFreqs[buzzer->noteIdx]]);
			int per = (100000 + freq / 2) / freq;
			__HAL_TIM_SET_COUNTER(buzzer->pwmTimer, 0);
			__HAL_TIM_SET_AUTORELOAD(buzzer->pwmTimer, per);
			__HAL_TIM_SET_COMPARE(buzzer->pwmTimer, TIM_CHANNEL_1, (per /2));
		}

		buzzer->maxCounter = FullLen >> buzzer->noteLengths[buzzer->noteIdx];
		buzzer->counter = 0;
		buzzer->noteIdx = (buzzer->noteIdx + 1) % buzzer->notesCount;

		if (buzzer->noteIdx == 0) {
			HAL_TIM_Base_Stop_IT(buzzer->pwmTimer);
			HAL_TIM_PWM_Stop(buzzer->pwmTimer, TIM_CHANNEL_1);
		}
	}
	buzzer->counter++;
}

void buzzerPlay(Buzzer * buzzer)
{
	buzzer->state = BUZ_STATE_MUSIC;

	HAL_TIM_PWM_Start(buzzer->pwmTimer, TIM_CHANNEL_1);
	HAL_TIM_Base_Start(buzzer->pwmTimer);
}

void buzzerPause(Buzzer * buzzer)
{
	buzzer->state = BUZ_STATE_OFF;

	HAL_TIM_Base_Stop(buzzer->pwmTimer);
	HAL_TIM_PWM_Stop(buzzer->pwmTimer, TIM_CHANNEL_1);
}

void buzzerPlayTone(Buzzer * buzzer, int frequency)
{
	buzzer->state = BUZ_STATE_TONE;

	int per = (100000 + frequency / 2) / frequency;
	__HAL_TIM_SET_COUNTER(buzzer->pwmTimer, 0);
	__HAL_TIM_SET_AUTORELOAD(buzzer->pwmTimer, per);
	__HAL_TIM_SET_COMPARE(buzzer->pwmTimer, TIM_CHANNEL_1, (per /2));

	HAL_TIM_PWM_Start(buzzer->pwmTimer, TIM_CHANNEL_1);
	HAL_TIM_Base_Start(buzzer->pwmTimer);
}

void buzzerPlayPause(Buzzer * buzzer)
{
	if (buzzer->state != BUZ_STATE_OFF) {
		buzzerPlay(buzzer);
	}
	else {
		buzzerPause(buzzer);
	}

}

