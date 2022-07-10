/*
 * AccessTask.c
 */

#include "main.h"
#include "Led.h"
#include "Rtc.h"
#include "Buzzer.h"
#include <string.h>
#include <stdio.h>


#define MAX_SOFT_FAILS   3
#define MAX_HARD_FAILS   9
#define SOFT_FAIL_LOCK_TIME_MS 30000
#define HARD_FAIL_LOCK_TIME_MS 300000

#define MAX_CODE_SIZE       9
#define MEM_CODE_ADDR       0x10
#define MEM_FAIL_COUNT_ADDR 0x20
#define MEM_FAIL_TIME_ADDR  0x24


extern Led ledB;
extern Led ledR;
extern Buzzer buzzer;
extern Rtc rtc;

static int _isSoftFail = 0;
static int _isHardFail = 0;
static int _softFailCount = 0;
static int _hardFailCount = 0;
static int _softFailTimeCount = 0;
static int _hardFailTimeCount = 0;


void accessInit()
{
	_softFailCount = 0;
	_isSoftFail = 0;
	_isHardFail = 0;

	// check if the system is in hard lock
	rtcRead(&rtc, MEM_FAIL_COUNT_ADDR, (uint8_t *)&_hardFailCount, sizeof(_hardFailCount));

	if (_hardFailCount >= MAX_HARD_FAILS) {

		uint32_t currentTime = rtcGetSeconds(&rtc);
		uint32_t failTime = 0;
		rtcRead(&rtc, MEM_FAIL_TIME_ADDR, (uint8_t *)&failTime, sizeof(failTime));

		// calculate remaining lock time in ms
		_hardFailTimeCount = (currentTime - failTime) * 1000;

		if (_hardFailTimeCount <= HARD_FAIL_LOCK_TIME_MS) {
			// the system is still in lock

			ledBlink(&ledR, 300);
			_isHardFail = 1;
		}
		else {
			// reset hard lock count
			_hardFailCount = 0;
			rtcWrite(&rtc, MEM_FAIL_COUNT_ADDR, (uint8_t *)&_hardFailCount, sizeof(_hardFailCount));
		}
	}
}

void accessOnTimerInterrupt()
{
	if (_isHardFail) {
		_hardFailTimeCount++;
		if (_hardFailTimeCount > HARD_FAIL_LOCK_TIME_MS) {
			// hard fail lock time up
			_isHardFail = 0;
			ledOff(&ledR);

			// reset hard lock count
			_hardFailCount = 0;
			rtcWrite(&rtc, MEM_FAIL_COUNT_ADDR, (uint8_t *)&_hardFailCount, sizeof(_hardFailCount));
		}
	}

	if (_isSoftFail) {
		_softFailTimeCount++;
		if (_softFailTimeCount > SOFT_FAIL_LOCK_TIME_MS) {
			// hard fail lock time up
			_isSoftFail = 0;
			_softFailCount = 0;
		}
	}
}

void accessSetCode(char * code)
{
	rtcWrite(&rtc, MEM_CODE_ADDR, (uint8_t *)code, MAX_CODE_SIZE);
	printf("Code set\r\n");
}

static void accessGranted()
{
	ledOn(&ledB);
	_softFailCount = 0;
	_hardFailCount = 0;

	rtcWrite(&rtc, MEM_FAIL_COUNT_ADDR, (uint8_t *)&_hardFailCount, sizeof(_hardFailCount));

	printf("Access granted\r\n");
}

static void accessDenied()
{
	printf("Invalid code\r\n");
	buzzerPlayTone(&buzzer, 200, 1000);

	_softFailCount++;
	_hardFailCount++;

	rtcWrite(&rtc, MEM_FAIL_COUNT_ADDR, (uint8_t *)&_hardFailCount, sizeof(_hardFailCount));

	if (_hardFailCount >= MAX_HARD_FAILS) {
		printf("Too many error tries. The system has been locked for 5 min\r\n");

		ledBlink(&ledR, 300);

		uint32_t failTime = rtcGetSeconds(&rtc);
		rtcWrite(&rtc, MEM_FAIL_TIME_ADDR, (uint8_t *)&failTime, sizeof(failTime));

		_hardFailTimeCount = 0;
		_isHardFail = 1;
	}
	else if (_softFailCount >= MAX_SOFT_FAILS){
		printf("Too many error tries. The system has been locked for 30 sec\r\n");

		_softFailTimeCount = 0;
		_isSoftFail = 1;
	}
}

void accessCheckCode(char * code)
{
	char savedCode[MAX_CODE_SIZE];

	ledOff(&ledB);

	if (_isHardFail) {
		printf("The system is locked. Remaining lock time is %d sec\r\n",
				(HARD_FAIL_LOCK_TIME_MS - _hardFailTimeCount) / 1000);
		return;
	}
	if (_isSoftFail) {
		printf("The system is locked. Remaining lock time is %d sec\r\n",
				(SOFT_FAIL_LOCK_TIME_MS - _softFailTimeCount) / 1000 );
		return;
	}

	rtcRead(&rtc, MEM_CODE_ADDR, (uint8_t *)savedCode, MAX_CODE_SIZE);
	if (strcmp(code, savedCode) == 0) {
		accessGranted();
	}
	else {
		accessDenied();
	}
}
