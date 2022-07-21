#ifndef _Dht11_
#define _Dht11_

#include "main.h"


typedef enum Dht11State_
{
	DHT11_STATE_SLEEP,
	DHT11_STATE_INIT,
	DHT11_STATE_WAKING,
	DHT11_STATE_AWATING_RESPONE_START,
	DHT11_STATE_RECEIVING_BITS,
	DHT11_STATE_DATA_RECEIVED,
	DHT11_STATE_ERR,
	DHT11_STATE_SUCCESS

} Dht11State;


typedef struct Dht11_
{
	GPIO_TypeDef * gpioPort;
	uint16_t gpioPin;
	Dht11State state;
	double temperature;
	double humidity;
	int checkSum;
}Dht11;

void Dht11_init(Dht11 * dht);
//void Dht11_reciveData(Dht11 * dht);
void Dht11_Start(Dht11 * dht);
void Dht11_Start_Async(Dht11 *dht);
void Dht11_onGpioInterrupt(Dht11 *dht, uint16_t pin);
//void Dht11_setInput(Dht11 * dht);
//void Dht11_setOutput(Dht11 * dht);
//void Dht11_printTempHum(Dht11 * dht);

#endif
