/*
 * mymain.c
 */

#include "main.h"
#include "Led.h"
#include "Buzzer.h"
#include "Rtc.h"
#include "CommTask.h"
#include "AccessTask.h"
#include <string.h>
#include <stdio.h>

extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim6;

Led ledB;
Led ledR;
Buzzer buzzer;
Rtc rtc;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	ledOnTimerInterrupt(&ledB);
	ledOnTimerInterrupt(&ledR);

	buzzerOnTimerInterrupt(&buzzer);

	accessOnTimerInterrupt();
}


static void handleCommand()
{
	char cmd[20];
	char code[10];

	char * command = commLastCommand();

	int params = sscanf(command, "%s %s", cmd, code);

	if (params == 0)
	{
		return;
	}

	if (strcmp(cmd, "setcode") == 0 && params > 1)
	{
		accessSetCode(code);
	}
	else if (strcmp(cmd, "code") == 0 && params > 1)
	{
		accessCheckCode(code);
	}
	else if (strcmp(cmd, "time") == 0)
	{
		DateTime dateTime;
		rtcGetTime(&rtc, &dateTime);
		printf("%02d:%02d:%02d-%d-%02d/%02d/%02d\r\n",
				dateTime.hours, dateTime.min, dateTime.sec,
				dateTime.weekDay,
				dateTime.day, dateTime.month, dateTime.year);
	}
	else
	{
		printf("Invalid command\r\n");
		return;
	}
}


void myMain()
{
	HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
	HAL_TIM_Base_Start_IT(&htim6);

	ledInit(&ledB, LBLUE_GPIO_Port, LBLUE_Pin);
	ledInit(&ledR, LRED_GPIO_Port, LRED_Pin);

	buzzerInit(&buzzer, &htim3);

	rtcInit(&rtc, &hi2c1, 0xD0);

	accessInit();

	while (1) {
		if (commTask()) {
			handleCommand();
		}

	}
}

