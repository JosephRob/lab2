#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include "utility.h"
#include "myshell.h"

int main(){
//    int hold=_dup(1);
//    FILE * f=fopen("text.txt","w");
    freopen("test","a",stdout);
    printf("asdf\n");
    fflush(stdout);
    fclose(stdout);
}