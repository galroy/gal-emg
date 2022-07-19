/*
 * CommTask.h
 */

#ifndef INC_COMMTASK_H_
#define INC_COMMTASK_H_
#include "cli.h"
int commTask();
char * commLastCommand();
void RegisterCommand(char *comand,char *stat,HandlerFunc hendler,void *obj);
//typedef void (*HandlerFunc)(void*);

#endif /* INC_COMMTASK_H_ */
