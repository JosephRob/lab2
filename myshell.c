/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2017, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include "utility.h"
#include "myshell.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256

// Put global environment variables here

// Define functions declared in myshell.h here

int main(int argc, char *argv[])
{
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
    char command[BUFFER_LEN] = { 0 };
    char arg[BUFFER_LEN] = { 0 };
    char wd[256];

    // Parse the commands provided using argc and argv
    printf("%s\t",getcwd(wd, 256));
    // Perform an infinite loop getting command input from users
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        // Perform string tokenization to get the command and argument
        char tok[]=" \n";
        for(int x =0;x <BUFFER_LEN;x ++){
            if (buffer[x]=='\n'){
                buffer[x]=' ';
            }
        }

        strcpy(command,strtok(buffer,tok));
        //printf("%s\n",command);
        // Check the command and execute the operations for each command
        // cd command -- change the current directory
        if (strcmp(command, "cd") == 0)
        {   
            strcpy(command,strtok(NULL," "));
            printf("%s\n",command);
        }

        // other commands here...
        else if (strcmp(command, "help") == 0){
            
        }
        // quit command -- exit the shell
        else if (strcmp(command, "quit") == 0)
        {
            return EXIT_SUCCESS;
        }
        else if (strcmp(command, "dir") == 0){

        }
        else if (strcmp(command, "clr") == 0){

        }
        else if (strcmp(command, "echo") == 0){

        }
        else if (strcmp(command, "pause") == 0){

        }

        // Unsupported command
        else
        {
            fputs("Unsupported command, use help to display the manual\n", stderr);
        }
        printf("%s\t",getcwd(wd, 256));
    }
    return EXIT_SUCCESS;
}
