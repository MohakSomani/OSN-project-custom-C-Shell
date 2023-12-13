#include "headers.h"

void ping(char* input)
{
    char* delim="   \n\0\t";
    char* tok=strtok(input,delim);
    int pid=atoi(tok);
    tok=strtok(NULL,delim);
    int signal=atoi(tok);
    signal%=32;
    // printf("%d %d\n",pid,signal);
    if(kill(pid,signal)==-1)
    {
        printf("No such process found\n");
    }else
    printf("Sent signal %d to process with pid %d\n",signal,pid);
}