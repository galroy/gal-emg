/*
 * buzzer.h
 *
 *  Created on: Jul 5, 2022
 *      Author: student
 */

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

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
	int noteIdx;
	int notesCount;
	const int * noteFreqs;
	const int * noteLengths;
} Buzzer;

void buzzerInit(Buzzer * buzzer, TIM_HandleTypeDef* pwmTimer);
void buzzerOnTimerInterrupt(Buzzer * buzzer);
void buzzerPlay(Buzzer * buzzer);
void buzzerPause(Buzzer * buzzer);
void buzzerPlayPause(Buzzer * buzzer);
void buzzerPlayTone(Buzzer * buzzer, int frequency);

#endif /* INC_BUZZER_H_ */
