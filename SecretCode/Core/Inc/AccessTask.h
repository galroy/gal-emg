/*
 * Accessask.h
 */

#ifndef ACCESSTASK_H_
#define ACCESSTASK_H_

void accessInit();

void accessOnTimerInterrupt();

void accessSetCode(char * code);

void accessCheckCode(char * code);

#endif /* ACCESSTASK_H_ */
