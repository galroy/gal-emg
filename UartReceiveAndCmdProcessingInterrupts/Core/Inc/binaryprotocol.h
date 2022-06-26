/*
 * binaryprotocol.h
 *
 *  Created on: Jun 7, 2022
 *      Author: student
 */

#ifndef INC_BINARYPROTOCOL_H_
#define INC_BINARYPROTOCOL_H_

#include <stdint.h>

struct MessageHeader
{
	uint8_t length;
	uint8_t messageId;
	uint8_t sequencId;
	uint8_t checksum;
};

enum MessageID{
	MSG_ID_NO = 0,
	MSG_ID_START = 1,
	MSG_ID_STOP = 2,
	MSG_ID_ON = 3
};

enum {
		MAX_PAYLOAD_SIZE = 20,
		SOM_SYMBOL = 0xAA,
};

struct Message
{
	uint8_t SOM;
	struct MessageHeader Header;
	uint8_t Payload[MAX_PAYLOAD_SIZE];
};
uint8_t stateMachine(uint8_t ch);
#endif /* INC_BINARYPROTOCOL_H_ */
