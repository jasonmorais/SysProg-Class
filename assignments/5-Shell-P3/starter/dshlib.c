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


void executePipeCommands(command_list_t *clist) {
    int numCommands = clist->num;
    int pipeFds[2 * (numCommands - 1)];

    for (int i = 0; i < numCommands - 1; i++) {
        if (pipe(pipeFds + i * 2) == -1) {
            perror("pipe");
            return;
        }
    }

    for (int i = 0; i < numCommands; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            if (i > 0) {
                if (dup2(pipeFds[(i - 1) * 2], STDIN_FILENO) == -1) {
                    perror("dup2 input");
                    exit(1);
                }
            }

            if (i < numCommands - 1) {
                if (dup2(pipeFds[i * 2 + 1], STDOUT_FILENO) == -1) {
                    perror("dup2 output");
                    exit(1);
                }
            }

            for (int j = 0; j < 2 * (numCommands - 1); j++) {
                close(pipeFds[j]);
            }

            if (execvp(clist->commands[i].argv[0], clist->commands[i].argv) == -1) {
                perror("execvp");
                exit(1);
            }
        }
    }

    for (int i = 0; i < 2 * (numCommands - 1); i++) {
        close(pipeFds[i]);
    }

    for (int i = 0; i < numCommands; i++) {
        wait(NULL);
    }
}




int build_cmd_list(char *cmd_line, command_list_t *clist) {
    int commandCount = 0;
    char* commandPointer;

    while ((commandPointer = strtok_r(cmd_line, "|", &cmd_line)) != NULL) {
        command_t newCommand;
        memset(&newCommand, 0, sizeof(command_t));

        if (*commandPointer == '\0') {
            continue;
        }

        if (commandCount >= CMD_MAX) {
            return ERR_TOO_MANY_COMMANDS;
        }

        char* subPointer = strtok_r(commandPointer, " ", &commandPointer);
        if (subPointer != NULL) {
            strcpy(newCommand.exe, subPointer);
        }

        while ((subPointer = strtok_r(commandPointer, " ", &commandPointer)) != NULL) {
            int argSize = sizeof(newCommand.args) - 1;
            strcat(newCommand.args, subPointer);
            newCommand.args[argSize] = '\0';
        }

        cmd_buff_t cmd_buff;
        memset(&cmd_buff, 0, sizeof(cmd_buff_t));
        cmd_buff.argv[0] = strdup(newCommand.exe);

        int arg_idx = 1;
        char *arg = strtok(newCommand.args, " ");
        while (arg != NULL) {
            if (strncmp(arg, "-e", 2) == 0) {
                cmd_buff.argv[arg_idx++] = strdup(arg);
            } else {
                cmd_buff.argv[arg_idx++] = strdup(arg);
            }
            arg = strtok(NULL, " ");
        }

        clist->commands[commandCount++] = cmd_buff;
    }

    clist->num = commandCount;
    if (commandCount == 0) {
        return ERR_CMD_OR_ARGS_TOO_BIG;
    }

    return OK;
}


int exec_local_cmd_loop()
{
    int rc = 0;
    char* cmd_buff = malloc(ARG_MAX * sizeof(char));

    while(1){
        printf("%s", SH_PROMPT);
        if (fgets(cmd_buff, ARG_MAX, stdin) == NULL){
            printf("\n");
            break;
        }
        // Remove the trailing newline from cmd_buff
        cmd_buff[strcspn(cmd_buff, "\n")] = '\0';

        if (cmd_buff[0] == '\0' || isAllSpaces(cmd_buff)){
            printf(CMD_WARN_NO_CMD);
            continue;
        }

        if (strcmp(cmd_buff, EXIT_CMD) == 0){
            exit(EXIT_SUCCESS);
        }

        command_list_t commandList;
        memset(&commandList, 0, sizeof(command_list_t));

        rc = build_cmd_list(cmd_buff, &commandList);

        if (rc == OK) {
            executePipeCommands(&commandList);
        } else {
            switch (rc) {
                case ERR_TOO_MANY_COMMANDS:
                    printf(CMD_ERR_PIPE_LIMIT, 8);
                    break;
                case ERR_MEMORY:
                    printf("Memory allocation error\n");
                    break;
                case WARN_NO_CMDS:
                    printf(CMD_WARN_NO_CMD);
                    break;
                default:
                    printf("Error: Command execution failed\n");
                    break;
            }
        }
        
    }

    free(cmd_buff);
    return OK;
}
