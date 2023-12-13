#ifndef HEADERS_H_
#define HEADERS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>   //for the system calls
#include <sys/stat.h> //for mkdir()
#include <fcntl.h>    //for the MACROS
#include <pwd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <grp.h>
#include <time.h>
#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <ctype.h>
#include <setjmp.h>
#include <termios.h>
#include <netdb.h>
#include <arpa/inet.h>


//Linked List
struct node{
    char* cmd;
    pid_t pid;
    struct node* next;
};
typedef struct node* Node;



//Queue
struct que
{
    char** arr;
    int start;
    int end;
    int numelems;
};

typedef struct que* Que;
extern Node activity;
extern int stdout_bkp;
extern int stdin_bkp;



// Text color
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[37m"
#define RESET   "\x1b[0m" 

// Text formatting
#define BOLD          "\x1b[1m" 
#define UNDERLINE     "\x1b[4m" 
#define ITALIC        "\x1b[3m" 
extern Que Q;
extern char* pastpath;

#include "functions.h"


#endif