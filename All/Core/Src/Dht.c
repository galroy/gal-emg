/*
 * Dht.c
 *
 *  Created on: Jul 18, 2022
 *      Author: USER-PC
 */
/*

 GPIO_InitStruct.Pin = DHT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_MODE_OUTPUT_PP
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DHT_GPIO_Port, &GPIO_InitStruct);

  #define DHT_Pin GPIO_PIN_5
#define DHT_GPIO_Port GPIOB
 */

#include "Dht.h"
#include "main.h"

extern GPIO_InitTypeDef GPIO_InitStruct;


static void setPinOutput()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = DHT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;

	HAL_GPIO_Init(DHT_GPIO_Port, &GPIO_InitStruct);
}

static void setPinInput()
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DHT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(DHT_GPIO_Port, &GPIO_InitStruct);

}
void DHT11_Start (void)
{
	setPinOutput();
	//Set_Pin_Output (DHT_GPIO_Port, DHT_Pin);  // set the pin as output
	HAL_GPIO_WritePin (DHT_GPIO_Port, DHT_Pin, 0);   // pull the pin low
	//delay (18000);   // wait for 18ms
	HAL_Delay(18000);
	//Set_Pin_Input(DHT_GPIO_Port, DHT_Pin);    // set as input
	setPinInput();
}

uint8_t Check_Response (void)
{
	//uint8_t Response = 0;
	int Response = 0;
	//delay (40);
	HAL_Delay(40);
	if (!(HAL_GPIO_ReadPin (DHT_GPIO_Port, DHT_Pin)))
	{
		//delay (80);
		HAL_Delay(80);
		if ((HAL_GPIO_ReadPin (DHT_GPIO_Port, DHT_Pin))){
			Response = 1;
		}
		else{
			Response = -1;
		}
	}
	while ((HAL_GPIO_ReadPin (DHT_GPIO_Port, DHT_Pin)));   // wait for the pin to go low

	return Response;
}

uint8_t DHT11_Read (void)
{
	uint8_t i,j;
	for (j=0;j<8;j++)
	{
		while (!(HAL_GPIO_ReadPin (DHT_GPIO_Port, DHT_Pin)));   // wait for the pin to go high
		//delay (40);   // wait for 40 us
		HAL_Delay(40);
		if (!(HAL_GPIO_ReadPin (DHT_GPIO_Port, DHT_Pin)))   // if the pin is low
		{
			i&= ~(1<<(7-j));   // write 0
		}
		else i|= (1<<(7-j));  // if the pin is high, write 1
		while ((HAL_GPIO_ReadPin (DHT_GPIO_Port, DHT_Pin)));  // wait for the pin to go low
	}
	return i;
}
