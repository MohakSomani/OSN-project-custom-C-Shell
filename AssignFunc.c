/*return 1 if assigned successfully , else 0
if 0 returned then try running it as a shell command(spec 6)*/

#include "headers.h"

int AssignFunc(char *input, char **prev, const char *home, char **fgprompt,Que Q,char* pastpath,char* in_global,Node head)
{
    // printf("\nAssignFunc() Called\n");
    char delim[] = "          \n\t\0";
    char *saveptr;
    char *in_cpy = strdup(input);
    char *token = strtok_r(input, delim, &saveptr);
    // printf("%s\n",token);
    if (token == NULL)
    {
        printf("Not valid\n");
        return 1;
    }
    if (strcmp(token, "warp") == 0)
    {
        warp(saveptr, prev, home, 1);
        return 1;
    }
    else if (strcmp(token, "peek") == 0)
    {
        peek(saveptr, prev, home);
        return 1;
    }
    else if (strcmp(token, "proclore") == 0)
    {
        proclore(saveptr, home);
        return 1;
    }
    else if (strcmp(token, "pastevents") == 0)
    {
        pastevent(saveptr, prev, home, fgprompt,Q,pastpath,in_global,head);
        return 1;
    }
    else if (strcmp(token, "seek") == 0)
    {
        seek(saveptr, home, prev);
        return 1;
    }
    else if (strcmp(token, "help") == 0)
    {
        help();
        return 1;
    }
    else if (strcmp(token, "exit") == 0)
    {
        exit_handler(Q,pastpath);
    }else if (strcmp(token, "ping") == 0)
    {
        ping(saveptr);
        return 1;
    }
    else if (strcmp(token, "activities") == 0)
    {
        activities();
        return 1;
    }
    else if (strcmp(token, "neonate") == 0)
    {
        neonate(saveptr);
        return 1;
    }else if (strcmp(token, "iMan") == 0)
    {
        iman(saveptr);
        return 1;
    }else if (strcmp(token, "fg") == 0)
    {
        send_fg(saveptr);
        return 1;
    }else if (strcmp(token, "bg") == 0)
    {
        send_bg(saveptr);
        return 1;
    }
    else
    {
        char* in_cpy2=strdup(in_cpy);
        char* tok=strtok(in_cpy2,delim);
        int c=0;
        while(tok)
        {
            c++;
            tok=strtok(NULL,delim);
        }
        char* arr[c+1];
        tok=strtok(in_cpy,delim);
        int n=0;
        while(tok)
        {
            arr[n++]=strdup(tok);
            tok=strtok(NULL,delim);
        }
        arr[n]=NULL;
        execvp(arr[0],arr);
        return 0;
    }

    return 0;
}