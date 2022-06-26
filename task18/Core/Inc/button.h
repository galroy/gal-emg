/*
 * button.h
 *
 *  Created on: Jun 19, 2022
 *      Author: student
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

typedef enum btnstate_{
	BUZZER_ON,
	BUZZER_OFF,
} BUZZER_STATE;
//{ 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494}
//Do,   Do#, Re,   R#,    Mi,   Fa,   F#,   Sol,  Sol#, La,   La#,  Si
/*typedef enum freq_{
	FREQ_DO,
	FREQ_DOH,
	FREQ_RE,

};*/

typedef struct _buzzer{
	BUZZER_STATE buzzerState;
} BUZZER;
void buzzerInit(BUZZER* bzr);
void buzzerOn(BUZZER* bzr);
void buzzerOff(BUZZER* bzr);
void buzzerOnFreq(BUZZER* bzr,uint8_t freq);
uint8_t GetTav(uint8_t freq);



#endif /* INC_BUTTON_H_ */
