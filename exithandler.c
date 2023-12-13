#include "headers.h"

void exit_handler(Que Q,char* pastpath)
{
    Enque(Q,"exit\n");
    SaveEntries(Q,pastpath);
    printf("\n");
    exit(1);
}
