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
    char * A=argv[1];
    //printf("%s\t%d\n",A,A!=0);
    if(A!=0){
        freopen(A,"r",stdin);
    }

    //printf("%d\n",strcmp(argv[1],"(null)"));
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
    char command[BUFFER_LEN] = { 0 };
    char wd[256];
    char path[256];
    FILE * storein;
    strcpy(path,getcwd(wd,256));
    // Parse the commands provided using argc and argv
    printf("%s/myshell $\t",path);

    // Perform an infinite loop getting command input from users
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        if(argv[1]!=0)printf("%s\n",buffer);
        // Perform string tokenization to get the command and argument
        const char tok[]=" \n";
        int count=0;
        for(int x =0;x <BUFFER_LEN;x ++){
            if (buffer[x]=='\n'){
                buffer[x]=' ';
            }
            else if(buffer[x]==' ' && buffer[x+1]!=' '){
                count++;
            }
        }
        count++;

        
        char parts[count][BUFFER_LEN];
        char *A;
        A=strtok(buffer,tok);
        //strcpy(parts[0],A);
        for (int x=0;x<count;x++){
            //printf("%s\n",A);
            strcpy(parts[x],A);
            A=strtok(NULL,tok);
            //printf("%s ",parts[x]);
        }
        strcpy(command,parts[0]);
        //printf("input: \t%s\n",command);
        
        //printf("%s\n",command);
        // Check the command and execute the operations for each command
        // cd command -- change the current directory

        for(int x=0;x<count;x++){
            if (strcmp(parts[x],"<")==0){
                //printf("%d\n",x);
                
                storein=fopen(parts[x+1],"r");//there is no input for each of the calls but if there were then they would be done with this stream
            }
            if (strcmp(parts[x],">")==0){
                printf("%d\t%s\n",x,parts[x+1]);
                freopen(parts[x+1],"w",stdout);
            }
        }

        if (strcmp(command, "cd") == 0)
        {   
            if(strcmp(parts[1],"..")==0){
                int place=0;
                for(int x=0;x<256;x++){
                    if(path[x]=='\0'){
                        break;
                    }
                    if(path[x]=='/')
                        place=x;
                }
                path[place]='\0';
            }
            else{
                strcat(path,"/");
                strcat(path,parts[1]);
            }
        }

        // other commands here...
        else if (strcmp(command, "help") == 0){
            int c;
            FILE *file;
            file = fopen("README", "r");
            if (file) {
                while ((c = getc(file)) != EOF)
                    putchar(c);
                fclose(file);
            }
            printf("\n");
        }
        // quit command -- exit the shell
        else if (strcmp(command, "quit") == 0)
        {
            return EXIT_SUCCESS;
        }
        else if (strcmp(command, "dir") == 0){
            //printf("%s\t%d\n",parts[1],count);
            DIR * d=opendir(path);
            if(count>1 && (strcmp(parts[1],"<")!=0) && (strcmp(parts[1],">")!=0)){
                d=opendir(parts[1]);
            }
            struct dirent *dir;
            if(d){
                while((dir=readdir(d))!=NULL){
                    printf("%s\n",dir->d_name);
                }
                closedir(d);
            }
        }
        else if (strcmp(command, "clr") == 0){
            //system("clear");
            printf("\e[1;H\e[2J");
        }
        else if (strcmp(command, "echo") == 0){
            for(int x=1;x<count;x++){
                printf("%s ",parts[x]);
            }
            printf("\n");
        }
        else if (strcmp(command, "pause") == 0){
            getchar();
        }
        else if(strcmp(command, "environ") == 0){
            system("printenv");
            /*for(char** env=envp;env!=0;env++){
                char * thisEnv=*env;
                printf("%s\n",thisEnv);
            }*/
        }

        // Unsupported command
        else
        {
            fputs("Unsupported command, use help to display the manual\n", stderr);
        }
        fflush(stdout);
        fclose(stdout);
        freopen("/dev/tty","a",stdout);
        
        printf("%s/myshell $\t",path);
    }
    printf("\n");
    return EXIT_SUCCESS;
}
