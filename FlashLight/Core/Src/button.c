/*
 * button.c
 *
 *  Created on: Jun 14, 2022
 *      Author: student
 */
#include "button.h"
void buttonInit(BUTTON* btn){
	if(btn == NULL){
		return;
	}
	btn->buttonState = BTN_UP;
	btn->counter = 0;
	btn->period = 0;
}
