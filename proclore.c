#include "headers.h"
#define MAX_BUF_SIZE 256
void proclore(char *input,const char* home)
{
    char delim[] = "   \t\n\0;";
    char *saveptr;
    char *token = strtok_r(input, delim, &saveptr);
    pid_t pid;
    if (token == NULL)
    {
        pid = getpid();
    }else
    {
        pid=atoi(token);
    }
        pid_t gpid = getpgid(pid);

        char proc_status_path[MAX_BUF_SIZE];
        unsigned long vsize;
        char exe_path[4097];
        char process_status;
        char status;

        // VIRTUAL MEMORY

        snprintf(proc_status_path, sizeof(proc_status_path), "/proc/%d/status", pid); // Corrected path

        FILE *pstatus_file = fopen(proc_status_path, "r");
        if (pstatus_file == NULL)
        {
            printf("proclore: Error in opening status file\n");
            return;
        }

        char line[MAX_BUF_SIZE];
        while (fgets(line, sizeof(line), pstatus_file) != NULL)
        {
            if (strncmp(line, "VmSize:", 7) == 0)
            {
                sscanf(line + 7, "%lu", &vsize);
            }
        }

        fclose(pstatus_file);

        // EXECUTIBLE PATH

        snprintf(exe_path, sizeof(exe_path), "/proc/%d/exe", pid);
        ssize_t len = readlink(exe_path, exe_path, sizeof(exe_path) - 1);
        if (len != -1)
        {
            exe_path[len] = '\0';
        }
        else
        {
            perror("readlink");
            return;
        }

        // Foreground-Background
        char fg = '+';
        pid_t tc_pgrp = tcgetpgrp(STDIN_FILENO);
            if (tc_pgrp==gpid)
            {
                fg = '+';
            }
            else
            {
                fg = ' ';
            }
        

        // STAT

        snprintf(proc_status_path, sizeof(proc_status_path), "/proc/%d/stat", pid);
        FILE *stat_file = fopen(proc_status_path, "r");
        if (stat_file == NULL)
        {
            printf("proclore: Error in opening stat file\n");
            exit(EXIT_FAILURE);
        }

        fscanf(stat_file, "%*d %*s %c", &process_status);
        // Reads some integer and discards . Reads some String and Discards and then reads a Character in the Variable
        fclose(stat_file);

        printf("pid : %d\nprocess Status : %c%c\nProcess Group : %d\nVirtual memory : %lu\nexecutable path : %s\n", pid, process_status, fg, gpid, vsize, path(exe_path,home));
    
    
}