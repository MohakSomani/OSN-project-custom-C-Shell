#include "headers.h"

void pipe_handle(char *in, char **prev, const char *home, char **fgprompt, Que Q, Node head, char *pastpath, char *in_global)
{
    if (strchr(in, '|') == NULL)
    {
        fgbg_assign(in, prev, home, fgprompt, Q, head, pastpath, in_global);
        return;
    }
    int pip_new[2];
    int pip_prev[2];
    // pip_new[0] - read
    // pip_new[1] - write
    char *saveptr = NULL;
    char *p_saveptr = strdup(in);
    char *tok = strtok_r(in, "|", &saveptr);

    // first process
    if (pipe(pip_new) == -1)
    {
        perror("pipe");
        return;
    }
    int f = fork();
    if (f < 0)
    {
        perror("fork");
        return;
    }
    if (f == 0)
    {
        close(pip_new[0]);
        dup2(pip_prev[0], STDIN_FILENO);
        close(pip_prev[0]);
        dup2(pip_new[1], STDOUT_FILENO);
        fgbg_assign(tok, prev, home, fgprompt, Q, head, pastpath, in_global);
        SaveEntries(Q, pastpath);
        exit(0);
    }
    if (f > 0)
    {
        // wait(NULL);
        close(pip_new[1]);
        close(pip_prev[0]);
        pip_prev[0] = pip_new[0];
        pip_prev[1] = pip_new[1];
        SaveEntries(Q, pastpath);
    }
    free(p_saveptr);
    p_saveptr = strdup(saveptr);
    tok = strtok_r(saveptr, "|", &saveptr);

    // pipe chain start
    while (strchr(p_saveptr, '|') != NULL)
    {
        if (pipe(pip_new) == -1)
        {
            perror("pipe");
            return;
        }
        int f = fork();
        if (f < 0)
        {
            perror("fork");
            return;
        }
        if (f == 0)
        {
            dup2(pip_prev[0], STDIN_FILENO);
            close(pip_prev[0]);
            close(pip_new[0]);
            dup2(pip_new[1], STDOUT_FILENO);
            // close(pip_new[1]);
            fgbg_assign(tok, prev, home, fgprompt, Q, head, pastpath, in_global);
            SaveEntries(Q, pastpath);

            exit(0);
        }
        if (f > 0)
        {
            wait(NULL);
            close(pip_new[1]);
            pip_prev[0] = pip_new[0];
            pip_prev[1] = pip_new[1];
        }
        free(p_saveptr);
        p_saveptr = strdup(saveptr);
        tok = strtok_r(saveptr, "|", &saveptr);
    }
    // last process
    dup2(stdout_bkp, STDOUT_FILENO);
    dup2(pip_prev[0], STDIN_FILENO);
    close(pip_prev[0]);
    fgbg_assign(tok, prev, home, fgprompt, Q, head, pastpath, in_global);
    dup2(stdin_bkp, STDIN_FILENO);
    dup2(stdout_bkp, STDOUT_FILENO);
    free(p_saveptr);
}