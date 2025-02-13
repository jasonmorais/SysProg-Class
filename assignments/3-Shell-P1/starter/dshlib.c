#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "dshlib.h"

/*
 *  build_cmd_list
 *    cmd_line:     the command line from the user
 *    clist *:      pointer to clist structure to be populated
 *
 *  This function builds the command_list_t structure passed by the caller
 *  It does this by first splitting the cmd_line into commands by spltting
 *  the string based on any pipe characters '|'.  It then traverses each
 *  command.  For each command (a substring of cmd_line), it then parses
 *  that command by taking the first token as the executable name, and
 *  then the remaining tokens as the arguments.
 *
 *  NOTE your implementation should be able to handle properly removing
 *  leading and trailing spaces!
 *
 *  errors returned:
 *
 *    OK:                      No Error
 *    ERR_TOO_MANY_COMMANDS:   There is a limit of CMD_MAX (see dshlib.h)
 *                             commands.
 *    ERR_CMD_OR_ARGS_TOO_BIG: One of the commands provided by the user
 *                             was larger than allowed, either the
 *                             executable name, or the arg string.
 *
 *  Standard Library Functions You Might Want To Consider Using
 *      memset(), strcmp(), strcpy(), strtok(), strlen(), strchr()
 */
int build_cmd_list(char *cmd_line, command_list_t *clist)
{
    int commandCount = 0;
    char* commandPointer;
    
    while((commandPointer = strtok_r(cmd_line, "|", &cmd_line)) != NULL){
        command_t newCommand;
        memset(&newCommand, 0, sizeof(command_t));

        if (*commandPointer == '\0') {
            continue;
        }

        if (commandCount >= CMD_MAX) {
            return ERR_TOO_MANY_COMMANDS;
        }

        char* subPointer = strtok_r(commandPointer, " ", &commandPointer);        
        strcpy(newCommand.exe, subPointer);

        while((subPointer = strtok_r(commandPointer, " ", &commandPointer)) != NULL){
            int argSize = sizeof(newCommand.args) - 1;
            strcat(newCommand.args, subPointer);
            newCommand.args[argSize] = '\0';
        }

        clist->commands[commandCount++] = newCommand;
    }

    clist->num = commandCount;
    if (commandCount == 0) {
        return ERR_CMD_OR_ARGS_TOO_BIG;
    }

    return OK;
}