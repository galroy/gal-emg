/*
 * buzzer.h
 *
 *  Created on: Jun 21, 2022
 *      Author: student
 */


#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "MyMain.h"

typedef enum buzzerstate_{
	BUZZER_ON,
	BUZZER_OFF,
} BUZZER_STATE;

typedef struct _buzzer{
	BUZZER_STATE buzzerState;
} BUZZER;
void buzzerInit(BUZZER* bzr);
void buzzerOn(BUZZER* bzr);
void buzzerOff(BUZZER* bzr);
void buzzerOnFreq(BUZZER* bzr,uint8_t freq);
uint8_t GetTav(uint8_t freq);


#endif /* INC_BUZZER_H_ */
