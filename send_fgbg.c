#include "headers.h"

void send_fg(char *in)
{
    char *delim = "       \n\t\0";
    char *tok = strtok(in, delim);
    int pid = atoi(tok);
    if (kill(pid, 0) == -1)
    {
        if (errno == ESRCH)
        {
            fprintf(stderr, "No such process found\n");
        }
        else
        {
            perror("kill");
        }
        return ;
    }

    if (kill(pid, SIGCONT) == -1)
    {
        perror("kill");
        return ;
    }
    int st;
    waitpid(pid,&st,WUNTRACED);
    // if (tcsetpgrp(STDIN_FILENO, pid) == -1)
    // {
    //     perror("tcsetpgrp");
    //     return;
    // }
    // if (tcsetpgrp(STDIN_FILENO, getpid()) == -1)
    // {
    //     perror("tcsetpgrp");
    //     return;
    // }
}

void send_bg(char *in)
{
    char *delim = "       \n\t\0";
    char *tok = strtok(in, delim);
    int pid = atoi(tok);
    if (kill(pid, 0) == -1)
    {
        if (errno == ESRCH)
        {
            fprintf(stderr, "No such process found\n");
        }
        else
        {
            perror("kill");
        }
        return ;
    }

    if (kill(pid, SIGCONT) == -1)
    {
        perror("kill");
        return ;
    }
}