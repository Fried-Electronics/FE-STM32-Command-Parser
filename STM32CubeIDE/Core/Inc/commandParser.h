/*
 * commandParser.h
 *
 *  Created on: Mar 12, 2023
 *      Author: Tom Fry
 */

#ifndef INC_COMMANDPARSER_H_
#define INC_COMMANDPARSER_H_

/*			Includes			*/
#include <stdint.h>

/*			Defines			*/
#define MAX_NUM_COMMANDS 10
#define MAX_NUM_ARGS 10

#define SERIAL_BUFFER_LENGTH 128

/*			Exported Types			*/
typedef struct SerialBuffer_t
{
	char charBuf[SERIAL_BUFFER_LENGTH];
	uint32_t tail;
} SerialBuffer_t;

/*			Exported Functions			*/
void Init_Command_Parser(SerialBuffer_t *SerialBuffer);
void Add_Command(char* CmdName, void *FunctionPointer);
void Read_Buffer(SerialBuffer_t *SerialBuffer);

#endif /* INC_COMMANDPARSER_H_ */
