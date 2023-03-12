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

/*			Types			*/
typedef struct CommandMap_t {
    char* cmdName;
    void (*funcPtr)(char**);
} CommandMap_t;

/*			Global Variables			*/
// Buffers
char g_serialBuf[SERIAL_BUFFER_LENGTH];
CommandMap_t g_cmdMap[MAX_NUM_COMMANDS];

// Variables
uint32_t g_numCmds = 0;
uint32_t g_serialBufIndex = 0;

/*			Function Prototypes			*/
void Add_Command (char* CmdName, void *FuncPtr);
void Process_Command(char* Cmd);

/*			Functions			*/
void Init_Command_Parser (void)
{

}

void Add_Command (char* CmdName, void *FuncPtr)
{
	g_cmdMap[g_numCmds].cmdName = CmdName;
	g_cmdMap[g_numCmds].funcPtr = FuncPtr;
	++g_numCmds;
}

void Read_Buffer (void)
{
	/*
    if (c == '\n') { // end of command
        buffer[buffer_index] = '\0'; // null-terminate the string
        buffer_index = 0; // reset the buffer index

        // process the command
        Process_Command(buffer);
    } else if (buffer_index < MAX_BUFFER_SIZE) { // add character to buffer
        buffer[buffer_index++] = c;
    }
    */
}

void Process_Command(char* Cmd) {
    char* token = strtok(Cmd, " ");
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
}
