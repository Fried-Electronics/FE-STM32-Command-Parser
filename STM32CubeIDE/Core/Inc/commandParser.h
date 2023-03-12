/*
 * commandParser.h
 *
 *  Created on: Mar 12, 2023
 *      Author: Tom Fry
 */

#ifndef INC_COMMANDPARSER_H_
#define INC_COMMANDPARSER_H_

/*			Defines			*/
#define MAX_NUM_COMMANDS 10
#define MAX_NUM_ARGS 10

#define SERIAL_BUFFER_LENGTH 128

/*			Exported Functions			*/
void Init_Command_Parser(void);
void Add_Command(char* CmdName, void *FunctionPointer);
void Read_Buffer(void);

#endif /* INC_COMMANDPARSER_H_ */
