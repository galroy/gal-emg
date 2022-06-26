/*
 * button.h
 *
 *  Created on: Jun 14, 2022
 *      Author: student
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

typedef enum buttonstate_{
	BTN_LONG_PRESS,
	BTN_SHORT_PRESS,
	BTN_UP,
	BTN_DOWN
} BUTTON_STATE;

typedef struct _button{
	BUTTON_STATE buttonState;
	int counter;
	int period;
} BUTTON;
void buttonInit(BUTTON* btn);


#endif /* INC_BUTTON_H_ */
