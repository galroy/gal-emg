#include "commTask.h"
#include <stdio.h>
#include <string.h>

extern UART_HandleTypeDef huart2;
//extern TIM_HandleTypeDef htim6;
//extern I2C_HandleTypeDef hi2c1;

/////////////////////////////////////////////////////////////////////////
// Communication task definitions and functions
/////////////////////////////////////////////////////////////////////////

#define MAX_BUFFER_LENGTH	100
#define MAX_COMMANDS		20

static uint8_t _cmdbuffer[MAX_BUFFER_LENGTH];
static int _cmdcount = 0;
static int _cmdprint = 0;

typedef struct command_
{
	char* comand;
	char* comandParam;
	HandlerFunc handler;
	void* obj;
}COMMAND;

COMMAND _commands[MAX_COMMANDS];
static int _counterComand = 0;

int _write(int fd, char *ptr, int len) {
	HAL_UART_Transmit(&huart2, (uint8_t*) ptr, len, HAL_MAX_DELAY);
	return len;
}

int commTask() {
	uint8_t ch;

	HAL_StatusTypeDef Status = HAL_UART_Receive(&huart2, &ch, 1, 10);
	if (Status != HAL_OK) {
		if ((huart2.Instance->ISR & USART_ISR_ORE) != 0) {
			__HAL_UART_CLEAR_OREFLAG(&huart2);
		}

		// here we have a time to print the command
		while (_cmdprint < _cmdcount) {
			HAL_UART_Transmit(&huart2, &_cmdbuffer[_cmdprint++], 1, 0xFFFF);
		}

		return 0;
	}

	if (ch == '\r' || ch == '\n') {
		// here we have a time to print the command
		while (_cmdprint < _cmdcount) {
			HAL_UART_Transmit(&huart2, &_cmdbuffer[_cmdprint++], 1, 0xFFFF);
		}

		HAL_UART_Transmit(&huart2, (uint8_t*) "\r\n", 2, 0xFFFF);

		_cmdbuffer[_cmdcount] = 0;
		_cmdcount = 0;
		_cmdprint = 0;

		// command is ready
		return 1;
	} else if (ch == '\b') {
		char bs[] = "\b \b";
		_cmdcount--;
		_cmdprint--;
		HAL_UART_Transmit(&huart2, (uint8_t*) bs, strlen(bs), 0xFFFF);
	} else {
		if (_cmdcount >= MAX_BUFFER_LENGTH) {
			_cmdcount = 0;
			_cmdprint = 0;
		}

		_cmdbuffer[_cmdcount++] = ch;
	}

	return 0;
}
void printCommands(){
	printf("command list\r\n");
	for(int i = 0; i< _counterComand;i++){
		printf("command = %s param=%s\r\n",_commands[i].comand,_commands[i].comandParam);
	}
}
void handleCommand() {
	char cmd[20] = {'\0'};
	char comandParam[20] = {'\0'};
	char param[20] = {'\0'};
	int i=0;
	int params = sscanf((const char*) _cmdbuffer, "%s %s %s", cmd, comandParam, param);
	if (params == 0) {
		return;
	}
	/*if(strcmp(cmd, "help") == 0) {
		printHelp();
		return;
	}*/
	for (i = 0; i < _counterComand; i++) {
		if (strcmp(cmd, _commands[i].comand) == 0) {

			if (strcmp(comandParam, _commands[i].comandParam) == 0) {

				//comands[i].handler(comands[i].obj);

				_commands[i].handler(_commands[i].obj, param);
				break;
			}
		}
	}


	if(i>=_counterComand){
		printf("Invalid command\r\n");
	}

}

void RegisterCommand(char *comand,char *comandParam,
		HandlerFunc handler, void *obj) {
	_commands[_counterComand].comand = comand;
	_commands[_counterComand].comandParam = comandParam;
	_commands[_counterComand].handler = handler;
	_commands[_counterComand].obj = obj;
	_counterComand++;

}

char* commLastCommand() {
	return (char*) _cmdbuffer;
}
