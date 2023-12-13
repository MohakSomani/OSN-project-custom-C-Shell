#include "headers.h"
Que Q;
char *pastpath;
jmp_buf env;
Node head;
int stdout_bkp;
int stdin_bkp;
Node activity;
volatile sig_atomic_t c_handle = 0, d_handle = 0, z_handle = 0;
void Ctrl_C_handler(int signal)
{
    // Call the exit handler when Ctrl+C is pressed
    if (c_handle)
    {
        printf("CTRL+C alrdy processing.\n");
        return;
    }
    c_handle = 1;
    printf("\n");
    if (head->pid != -1)
    {
        kill(head->pid, SIGINT);
        Deletepid(activity, head->pid);
    }
    head->pid = -1;
    c_handle = 0;
    longjmp(env, 1);
}
void Ctrl_D_handler(int signal)
{
    // printf("D press\n");
    exit_handler(Q, pastpath);
    exit(1);
}
void Ctrl_Z_handler(int signal)
{
    if (z_handle)
    {
        // printf("CTRL + Z already being processed\n");
        // Unblock the SIGTSTP signal before returning
        // longjmp(env, 1);
        return;
    }
    z_handle = 1;
    printf("\n");
    if (head->pid != -1)
    {
        if (kill(head->pid, 0) == 0)
        {
            LLAdd(head, head->cmd, head->pid);
            kill(head->pid, SIGTSTP);
            kill(head->pid, SIGSTOP);
        }
    }
    head->pid = -1;
    z_handle = 0;
    longjmp(env, 1);
}

int main()
{
    stdout_bkp = dup(STDOUT_FILENO);
    stdin_bkp = dup(STDIN_FILENO);

    FILE *STIN = stdin;
    signal(SIGINT, Ctrl_C_handler);
    signal(SIGQUIT, Ctrl_D_handler);
    signal(SIGTSTP, Ctrl_Z_handler);
    char *home = getcwd(NULL, 0);
    pastpath = (char *)malloc(strlen(home) + 10);
    strcpy(pastpath, home);
    pastpath = strcat(pastpath, "/past.txt");
    char *in_global = NULL;
    head = (Node)malloc(sizeof(struct node));
    activity = (Node)malloc(sizeof(struct node));
    head->cmd = NULL;
    head->next = NULL;
    head->pid = -1;
    Q = (Que)malloc(sizeof(struct que));
    Q->arr = (char **)malloc(sizeof(char *) * 15);
    Q->start = 0;
    Q->end = -1;
    Q->numelems = 0;
    RetrieveQue(Q, pastpath);
    char *prev = NULL;
    char *fgprompt = "";
    char *saveptr;
    sigsetjmp(env, 1);
    while (1)
    {
        dup2(stdout_bkp, STDOUT_FILENO);
        // Print appropriate prompt with username, systemname and directory before accepting input
        prompt(home, &fgprompt);
        char input[4096];
        Q->start = 0;
        Q->end = -1;
        Q->numelems = 0;
        RetrieveQue(Q, pastpath);
        if (stdin == NULL)
        {
            printf("STDIN is null\n");
        }
        if (fgets(input, 4096, stdin) == NULL)
        {
            if (errno == EINTR)
            {
                printf("fgets interrupted by a signal\n");
                // Handle the interruption gracefully if needed
            }
            if (feof(stdin)) // End of file
            {
                printf("End of file reached.\n");
                // free(input); // Free memory allocated by getline
            }
            else
            {
                perror("fgets error");
                // Handle other errors if needed
            }
            exit_handler(Q, pastpath);
        }
        // long unsigned int len = 0;
        // ssize_t read = getline(&input, &len, stdin);

        // // Check for end of file or error
        // if (read == -1)
        // {
        //     if (feof(stdin)) // End of file
        //     {
        //         printf("End of file reached.\n");
        //         free(input); // Free memory allocated by getline
        //         break;       // Exit the loop
        //     }
        //     else if (ferror(stdin)) // Error
        //     {
        //         perror("getline error");
        //         free(input); // Free memory allocated by getline
        //         exit_handler(Q, pastpath);
        //     }
        // }
        CheckCompleted(head);
        in_global = strdup(input);
        Enque(Q, input);
        char *tok = strtok_r(input, ";", &saveptr);
        while (tok && tok[0] != '\n')
        {
            // AssignFunc(tok, &prev, home, &fgprompt, Q, pastpath, in_global, head);

            pipe_handle(tok, &prev, home, &fgprompt, Q, head, pastpath, in_global);
            // AssignFunc(tok, &prev, home, &fgprompt);
            tok = strtok_r(saveptr, ";", &saveptr);
        }
        SaveEntries(Q, pastpath);
        dup2(0, STDIN_FILENO);
        dup2(1, STDOUT_FILENO);
        stdin = STIN;
    }
    Q = NULL;
}
