/*
 * commandParser.c
 *
 *  Created on: Mar 12, 2023
 *      Author: Tom Fry
 */

/*			Includes			*/
#include "commandParser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

/*			Types			*/
typedef struct CommandMap_t
{
    char* cmdName;
    void (*funcPtr)(char**);
} CommandMap_t;

/*			Global Variables			*/
// Buffers
CommandMap_t g_cmdMap[MAX_NUM_COMMANDS];

// Variables
uint32_t g_numCmds = 0;

/*			Function Prototypes			*/
static void Process_Command(SerialBuffer_t *SerialBuffer);
static void Clear_Buffer(SerialBuffer_t *SerialBuffer);

/*			Functions			*/
void Init_Command_Parser (SerialBuffer_t *SerialBuffer)
{
	Clear_Buffer(SerialBuffer);

	// Clear the command map
	for (int mapIndex = 0; mapIndex < MAX_NUM_COMMANDS; ++mapIndex)
	{
		g_cmdMap[mapIndex].cmdName = NULL;
		g_cmdMap[mapIndex].funcPtr = NULL;
	}
	// Clear the command counter
	g_numCmds = 0;
}

void Add_Command (char* CmdName, void *FuncPtr)
{
	g_cmdMap[g_numCmds].cmdName = CmdName;
	g_cmdMap[g_numCmds].funcPtr = FuncPtr;
	++g_numCmds;
}

void Read_Buffer (SerialBuffer_t *SerialBuffer)
{
	for (int bufIndex = 0; bufIndex < SERIAL_BUFFER_LENGTH; ++bufIndex)
	{
		if ('\n' == SerialBuffer->charBuf[bufIndex])
		{
			SerialBuffer->charBuf[bufIndex] = '\0';
			SerialBuffer->tail = bufIndex;

			Process_Command(SerialBuffer);
			break;
		}
	}
}

static void Process_Command (SerialBuffer_t *SerialBuffer)
{
    char* token = strtok(SerialBuffer->charBuf, " ");
    char* args[MAX_NUM_ARGS];
    uint32_t argCount = 0;

    while ((NULL != token) && (MAX_NUM_ARGS > argCount))
    {
        args[argCount++] = token;
        token = strtok(NULL, " ");
    }

    // map the command string to a command enum using the command_map array
    for (int cmdIndex = 0; cmdIndex < g_numCmds; ++cmdIndex)
    {
        if (0 == strcmp(args[0], g_cmdMap[cmdIndex].cmdName))
        {
            // call the appropriate function with the parsed arguments
            g_cmdMap[cmdIndex].funcPtr(&args[1]);
            break;
        }
    }

    Clear_Buffer(SerialBuffer);
}

static void Clear_Buffer (SerialBuffer_t *SerialBuffer)
{
	// Set the buffer to the NULL termination
	for (int bufIndex = 0; bufIndex < SERIAL_BUFFER_LENGTH; ++bufIndex)
	{
		SerialBuffer->charBuf[bufIndex] = '\0';
	}
	// Set the buffer head and tail to zero
	SerialBuffer->tail = 0;
}
