/*
 * dht.h
 *
 *  Created on: Jul 18, 2022
 *      Author: USER-PC
 */

#ifndef INC_DHT_H_
#define INC_DHT_H_
#include "main.h"

void DHT11_Start (void);
uint8_t Check_Response (void);
uint8_t DHT11_Read (void);
#endif /* INC_DHT_H_ */
