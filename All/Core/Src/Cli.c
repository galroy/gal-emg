#include <Cli.h>
#include "led.h"
#include "commTask.h"
#include <stdlib.h>
#include <stdio.h>


extern Led _ledRed;
extern Led _ledBlue;

uint8_t isNumber(const char *str) {

	if(*str == '\0'){
		return 0;
	}
	while (*str != '\0') {
		if (*str < '0' || *str > '9')
			return 0;
		str++;
	}
	return 1;
}

static void cmdledblueOn(void* obj,char *command){
	Led *led = (Led*)obj;
	ledOn(led);
}

static void cmdledblueOff(void* obj,char *command){
	Led *led = (Led*)obj;
	ledOff(led);
}

static void cmdledRedOn(void* obj,char *command){
	Led *led = (Led*)obj;
	ledOn(led);
}

static void cmdledRedOff(void* obj,char *command){
	Led *led = (Led*)obj;
	ledOff(led);
}

static void cmdLedBlueBlink(void* obj,char *command){
	Led *led = (Led*)obj;
	int period = 0;
	if(isNumber(command)){
		period = atoi(command);
		ledBlink(led,period);
	}else{
		printf("Invalid parameter\r\n");
	}


}

static void cmdLedRedBlink(void *obj, char *command) {
	Led *led = (Led*) obj;
	int period = 0;
	if (isNumber(command)) {
		period = atoi(command);
		ledBlink(led, period);
	} else {
		printf("Invalid parameter\r\n");
	}

}
static void cmdhelp(void *obj, char *command){
	(void)obj;
	(void)command;
	printCommands();
}

void cliInit(){
	//ledInit(&ledB, LD2_GPIO_Port, LD2_Pin);
	//ledInit(&ledR, LD3_GPIO_Port, LD3_Pin);
	//RegisterCommand("help", "", NULL, NULL);
	RegisterCommand("ledblue", "on", cmdledblueOn, &_ledBlue);
	RegisterCommand("ledblue", "off", cmdledblueOff, &_ledBlue);
	RegisterCommand("ledred", "on", cmdledRedOn, &_ledRed);
	RegisterCommand("ledred", "off", cmdledRedOff, &_ledRed);
	RegisterCommand("ledblue", "blink", cmdLedBlueBlink, &_ledBlue);
	RegisterCommand("ledred", "blink", cmdLedRedBlink, &_ledRed);

	RegisterCommand("help", "", cmdhelp, NULL);

	/*RegisterCommand("ledblue", ledOn, &_ledBlue);
	RegisterCommand("ledblue", ledOff, &_ledBlue);
	RegisterCommand("ledred", ledOn, &_ledRed);
	RegisterCommand("ledred", ledOff, &_ledRed);
	RegisterCommand("ledblue", ledBlink, &_ledBlue);
	RegisterCommand("ledred", ledBlink, &_ledRed);*/
}



