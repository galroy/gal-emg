/*
 * MyMain.c
 *
 *  Created on: Jun 21, 2022
 *      Author: student
 */
#include "MyMain.h"
#include "LedControl.h"
#include "buzzer.h"
#include "button.h"
#include "clock.h"

extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim6;
extern UART_HandleTypeDef huart2;


CLOCK mainClock;
BUTTON btnSW1;
BUTTON btnSW2;
LED ledR;
LED ledB;
BUZZER bzr;
GPIO_PinState pinState;

/*
 GPIO_PIN_RESET = 0U,
  GPIO_PIN_SET
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){


	//pinState = HAL_GPIO_ReadPin(B2_GPIO_Port, B2_Pin);
	//if(pinState == GPIO_PIN_SET){
	buttonOnInterrupt(&btnSW2,GPIO_Pin);

	//}

	/*
	if(pinState == GPIO_PIN_SET){
		ledOff(&ledB);
		ledOff(&ledR);
		HAL_TIM_Base_Stop_IT(&htim6);
		buzzerOff(&bzr);



	}else{
		ledOn(&ledB);
		ledOn(&ledR);
		uint8_t tmp;
		tmp = GetTav(262);
		buzzerOn(&bzr);
		buzzerOnFreq(&bzr,tmp);
		HAL_TIM_Base_Start_IT(&htim6);
	}
	*/


}

//start
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

	/*if(htim == &htim6){
		SetButtonNone(&btnSW2);
		//buzzerOnFreq(&bzr,390);

	}*/
	clockOnInterrupt(&mainClock,htim);
}
//end cicale
/*void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim){
	ledOff(&ledB);
}*/




  //HAL_TIM_Base_Init(&htim4);
  //HAL_TIM_Base_Start_IT(&htim4);

  //HAL_TIM_PWM_Start_IT(&htim4, TIM_CHANNEL_1);
  //setBrightness(&ledB, 10);
int _write(int fd, char* ptr, int len) {
	HAL_UART_Transmit(&huart2, (uint8_t *) ptr, len, HAL_MAX_DELAY);
	//UART_Transmit(&huart2, (uint8_t *) ptr, len);
    return len;
}
int mainLoop(){
	uint16_t sec = 0,clocksec=0;
	uint16_t min = 0,clockmin = 0;

	HAL_TIM_Base_Init(&htim4);
	HAL_TIM_Base_Start_IT(&htim4);

	HAL_TIM_PWM_Start_IT(&htim4, TIM_CHANNEL_1);

	HAL_TIM_Base_Init(&htim6);
	HAL_TIM_Base_Start_IT(&htim6);
	//setBrightness(&ledB, 10);
	clockInit(&mainClock,&htim6);
	buttonInit(&btnSW2,BTN_SW2,B2_GPIO_Port,B2_Pin);
	buzzerInit(&bzr);
	ledInit(&ledB,LD2_GPIO_Port,LD2_Pin);
	ledInit(&ledR, LD3_GPIO_Port, LD3_Pin);

	//ledOn(&ledB);
	//ledOn(&ledR);
	while(1){
		if(getButtonState(&btnSW2) == BUTTON_STATE_LONG_PRESS){
			ledOn(&ledB);

			printf("btn stat = %d\n\r",getButtonState(&btnSW2));
			SetButtonNone(&btnSW2);
			//btnSW2->buttonState = BUTTON_STATE_NONE;
		}

		if(getButtonState(&btnSW2) == BUTTON_STATE_PRESS){
			ledOff(&ledB);
			printf("btn stat = %d\n\r",getButtonState(&btnSW2));
			SetButtonNone(&btnSW2);
				//	btnSW2->buttonState = BUTTON_STATE_NONE;
		}
		clocksec = clockGetSecond(&mainClock);
		clockmin = clockGetMinute(&mainClock);
		if(sec != clocksec){
			printf("sec=%d\n\r",clocksec);
			sec = clocksec;
		}
		if(min != clockmin){
			printf("min=%d\n\r",clockmin);
			min = clockmin;
		}


	}
}


