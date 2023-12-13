#include "headers.h"

void help()
{
    printf(BOLD RED "\n===Welcome to Mohak's custom C-Shell===\n\n" RESET);
    printf(WHITE "Here is the list of custom commands which you can use in this shell along with all the bash commands :-\n" RESET);
    printf("\n1) " BOLD GREEN " warp      " RESET " :-   You can use this to change the current working directory \n                    of the terminal . It can work with relative paths as well\n                    as absolute paths . You can put multiple arguments for\n                    sequential directory changing .");
    printf("\n2) " BOLD GREEN " pastevents" RESET " :-   This command can be used to retrieve past history of the \n                    commands run in the terminal . Also you can \"purge\" the\n                    history stored till now . You can also \"execute\" the\n                    commands in the history again .");
    printf("\n3) " BOLD GREEN " peek      " RESET " :-   This command can be used to list names and info about the\n                     files , folders or executibles in the given directory . \n                   It has 2 flags \"-a\" & \"-l\" . \"-a\" is for listing \n                   everything including the hidden files . \"-l\" is for listing everything\n                     with detailed info about file permissions , hard links  , etc. \n");
    printf("\n4) " BOLD GREEN " seek      " RESET " :-   This command searches for files and folders with a given \n                    name . It has 3 flags \"-d\",\"-f\" & \"-e\" . \"-d\" lis\n                   ts only the directories with the given name . \"-f\" li\n                   sts only the files with the given name . \"-e\" if there is only one fil\n                    e/directory with the name , it changes directory into the folder \n                    if its a directory and it prints the contents of the file if its a file .\n");
    printf("\n5) " BOLD GREEN " proclore  " RESET " :-   This command lists out various details about a process , \n                    either the terminal or a process with a given process id \n                   . It lists down info like Process Id, Process Status , \n                   Process Group , Virtual Memory , Executable Path for the process .\n");
    printf(BOLD RED "\n=== === === === === === === === === === === === === === === === === === === === === === ===\n" RESET);
}