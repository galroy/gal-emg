/*
 * cli.c
 *
 *  Created on: 12 Jul 2022
 *      Author: student
 */

#include "main.h"
#include "led.h"
#include "cli.h"

Led _ledBlue;



void cliInit(){

	RegisterCommand("led","on","ledOn",&_ledBlue);
	RegisterCommand("led","off","ledOff",&_ledBlue);

}
void cmdLed(void *obj,char *cmd){
	if(strcmp(cmd, "on") == 0){
		ledOn(obj);
	}else if(strcmp(cmd, "off") == 0){
		ledOff(obj);
	}

}


