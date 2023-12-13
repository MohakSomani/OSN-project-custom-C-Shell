#include "headers.h"

void activities()
{
    Node L = activity->next;
    Node p = activity;

    while (L != NULL)
    {
        char proc_status_path[4096];
        int pid = L->pid;
        snprintf(proc_status_path, sizeof(proc_status_path), "/proc/%d/stat", pid);
        FILE *stat_file = fopen(proc_status_path, "r");
        if (stat_file == NULL)
        {
            Node temp = p->next->next;
            free(p->next);
            p->next = temp;
            p = L;
            L = L->next;
            continue;
        }
        if(L->cmd[strlen(L->cmd)-1]=='\n')
        {
            L->cmd[strlen(L->cmd)-1]=' ';
        }
        char process_status;
        fscanf(stat_file, "%*d %*s %c", &process_status);
        // Reads some integer and discards . Reads some String and Discards and then reads a Character in the Variable
        fclose(stat_file);
        // printf("%d : %s - ", L->pid, L->cmd);
        if (process_status == 'R' || process_status == 'S')
        {
            printf("%d : %s - Running\n", L->pid, L->cmd);
        }
        else if (process_status == 'T')
        {
            printf("%d : %s - Stopped\n", L->pid, L->cmd);
        }
        p = L;
        L = L->next;
    }
}