/*
 * handleCommand.c
 *
 *  Created on: Jul 3, 2022
 *      Author: student
 */

#ifndef INC_HANDLECOMMAND_C_
#define INC_HANDLECOMMAND_C_

#include "main.h"
#include <stdint.h>

typedef void(*HandlerFunc)(void*, char*);

/*typedef struct command_
{
	char* comand;
	char* comandParam;
	HandlerFunc handler;
	void* obj;
}COMMAND;
*/

int commTask();
char * commLastCommand();
void handleCommand();
void printCommands();
void RegisterCommand(char* comand, char *comandParam, HandlerFunc comandPointer, void* obj);
void RegisterCallbacks(HandlerFunc onFunc, HandlerFunc offFunc, void *obj);

#endif /* INC_HANDLECOMMAND_C_ */
