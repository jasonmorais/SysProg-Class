#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "dshlib.h"

/*
 * Implement your exec_local_cmd_loop function by building a loop that prompts the 
 * user for input.  Use the SH_PROMPT constant from dshlib.h and then
 * use fgets to accept user input.
 * 
 *      while(1){
 *        printf("%s", SH_PROMPT);
 *        if (fgets(cmd_buff, ARG_MAX, stdin) == NULL){
 *           printf("\n");
 *           break;
 *        }
 *        //remove the trailing \n from cmd_buff
 *        cmd_buff[strcspn(cmd_buff,"\n")] = '\0';
 * 
 *        //IMPLEMENT THE REST OF THE REQUIREMENTS
 *      }
 * 
 *   Also, use the constants in the dshlib.h in this code.  
 *      SH_CMD_MAX              maximum buffer size for user input
 *      EXIT_CMD                constant that terminates the dsh program
 *      SH_PROMPT               the shell prompt
 *      OK                      the command was parsed properly
 *      WARN_NO_CMDS            the user command was empty
 *      ERR_TOO_MANY_COMMANDS   too many pipes used
 *      ERR_MEMORY              dynamic memory management failure
 * 
 *   errors returned
 *      OK                     No error
 *      ERR_MEMORY             Dynamic memory management failure
 *      WARN_NO_CMDS           No commands parsed
 *      ERR_TOO_MANY_COMMANDS  too many pipes used
 *   
 *   console messages
 *      CMD_WARN_NO_CMD        print on WARN_NO_CMDS
 *      CMD_ERR_PIPE_LIMIT     print on ERR_TOO_MANY_COMMANDS
 *      CMD_ERR_EXECUTE        print on execution failure of external command
 * 
 *  Standard Library Functions You Might Want To Consider Using (assignment 1+)
 *      malloc(), free(), strlen(), fgets(), strcspn(), printf()
 * 
 *  Standard Library Functions You Might Want To Consider Using (assignment 2+)
 *      fork(), execvp(), exit(), chdir()
 */
int isAllSpaces(const char *str) {
    while (*str) {
        if (!isspace((unsigned char)*str)) {
            return 0; 
        }
        str++;
    }
    return 1;
}

void trimSpaces(char *str) {
    while (*str && isspace((unsigned char)*str)) str++;
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0'; 
}

int buildCommandBuff(char *cmdBufferInput, cmd_buff_t *cmd_buff) {
    int argc = 0;
    bool isQuotes = false;
    int cmdLen = strlen(cmdBufferInput);
    char *cmdBufferInputTemp = cmdBufferInput;
    char cmdArgBuffer[ARG_MAX];
    int cmdArgBufferIndex = 0;
    int x = 0;

    trimSpaces(cmdBufferInputTemp);
    memset(cmd_buff, 0, sizeof(cmd_buff_t));
    memset(cmdArgBuffer, 0, ARG_MAX);

    while (x < cmdLen) {
        if (cmdBufferInputTemp[x] == ' ' && !isQuotes) {
            if (cmdArgBufferIndex > 0) {
                cmd_buff->argv[argc] = strdup(cmdArgBuffer);
                argc++;
                memset(cmdArgBuffer, 0, ARG_MAX);
                cmdArgBufferIndex = 0;
            }
        }
        else if (cmdBufferInputTemp[x] == '"') {
            isQuotes = !isQuotes;
        }
        else {
            cmdArgBuffer[cmdArgBufferIndex++] = cmdBufferInputTemp[x];
        }
        x++;
    }

    if (cmdArgBufferIndex > 0) {
        cmd_buff->argv[argc] = strdup(cmdArgBuffer);
        argc++;
    }

    cmd_buff->argc = argc;
    return OK;
}


int executeExternalCommand(cmd_buff_t* cmd_buff){
    pid_t pid = fork();
    if(pid == 0){
        if(execvp(cmd_buff->argv[0], cmd_buff->argv) == -1){
            return ERR_EXEC_CMD;
        }
    }
    else{
        int status;
        waitpid(pid, &status, 0);
        if(WIFEXITED(status)){
            return OK;
        }
        else{
            return ERR_EXEC_CMD;
        }
    }
    return OK;
}


int executeCommand(cmd_buff_t* cmd_buff){
    char* commandName = cmd_buff->argv[0];
    if(strcmp("dragon", commandName) == 0){
        print_dragon();
    }
    else if(strcmp("cd", commandName) == 0){
        if (cmd_buff->argv[1] != NULL) {
            if (chdir(cmd_buff->argv[1]) != 0) {
                return ERR_EXEC_CMD;
            }
        }
    }
    else{
        executeExternalCommand(cmd_buff);
    }
    return OK;
}

int exec_local_cmd_loop()
{
    int rc = 0;
    cmd_buff_t cmd;
    char* cmd_buff = malloc(ARG_MAX * sizeof(char));

    while(1){
        printf("%s", SH_PROMPT);
        if (fgets(cmd_buff, ARG_MAX, stdin) == NULL){
            printf("\n");
            break;
        }
        //remove the trailing \n from cmd_buff
        cmd_buff[strcspn(cmd_buff, "\n")] = '\0';

        if(cmd_buff[0] == '\0' || isAllSpaces(cmd_buff)){
            printf(CMD_WARN_NO_CMD);
            continue;
        }

        if(strcmp(cmd_buff, EXIT_CMD) == 0){
            exit(EXIT_SUCCESS);
        }

        rc = buildCommandBuff(cmd_buff, &cmd);
        switch(rc){
            case OK:
                executeCommand(&cmd);
                break;

            case ERR_TOO_MANY_COMMANDS:
                printf(CMD_ERR_PIPE_LIMIT, 8);
                break;

            case ERR_CMD_OR_ARGS_TOO_BIG:
                printf(CMD_ERR_PIPE_LIMIT, 8);
                break;

            default:
                break;
        }
    }
    free(cmd_buff);
    // TODO IMPLEMENT MAIN LOOP

    // TODO IMPLEMENT parsing input to cmd_buff_t *cmd_buff

    // TODO IMPLEMENT if built-in command, execute builtin logic for exit, cd (extra credit: dragon)
    // the cd command should chdir to the provided directory; if no directory is provided, do nothing

    // TODO IMPLEMENT if not built-in command, fork/exec as an external command
    // for example, if the user input is "ls -l", you would fork/exec the command "ls" with the arg "-l"

    return OK;
}


