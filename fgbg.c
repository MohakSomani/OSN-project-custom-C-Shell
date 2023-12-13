#include "headers.h"

void fgbg_assign(char *in, char **prev, const char *home, char **fgprompt, Que Q, Node head, char *pastpath, char *in_global)
{

    char *in_cpy = strdup(in);
    char delim[] = "          \t\n\0";
    int app = 0;
    char *o_red = strchr(in, '>');
    char *o_file = NULL;
    if (o_red != NULL)
    {
        if (strchr(o_red + 1, '>') == NULL)
            o_file = strtok(strdup(o_red) + 1, delim);
        else
        {
            app = 1;
            o_file = strtok(strdup(o_red) + 2, delim);
        }
        char *tmp = strstr(o_red, o_file);
        strcpy(o_red, tmp + strlen(o_file));
    }
    char *in_cp2 = strdup(in);
    char *in_cp3 = strdup(in);
    char *i_red = strchr(in_cp2, '<');
    char *i_file = NULL;
    if (i_red != NULL)
    {
        // *i_red = '\0';
        i_file = strtok(strdup(i_red) + 1, delim);
        char *tmp = strstr(in_cp2, i_file);
        char *tmp2 = strdup(tmp + strlen(i_file));

        //
        int file_descriptor;
        char *contents;
        off_t file_size;
        file_descriptor = open(i_file, O_RDONLY);
        if (file_descriptor == -1)
        {
            perror("Error opening file");
            return;
        }
        file_size = lseek(file_descriptor, 0, SEEK_END);
        lseek(file_descriptor, 0, SEEK_SET);

        contents = (char *)malloc(file_size + 1);
        if (contents == NULL)
        {
            perror("Error allocating memory");
            close(file_descriptor);
            return;
        }

        ssize_t bytes_read = read(file_descriptor, contents, file_size);
        if (bytes_read == -1)
        {
            perror("Error reading file");
            free(contents);
            close(file_descriptor);
            return;
        }
        contents[bytes_read] = '\0';
        close(file_descriptor);
        // printf("File contents:\n%s\n", contents);
        //
        strcpy(in_cp3 + (i_red - in_cp2), strdup(tmp2));
        strcpy(i_red, contents);
        // printf("%s\n", in);
        in_cp3 = strdup(in_cp3);
        strcat(in_cp2, tmp2);
        free(contents);
    }

    // printf("2:  %s\n3:  %s\n", in_cp2,in_cp3);

    // printf("%s\n", in);
    // printf("in: %s\n", i_file);
    // printf("out: %s\n", o_file);
    char *saveptr;
    char *token = strtok_r(in_cpy, delim, &saveptr);
    int amp_flag = 0;
    while (token && token[0] != '\n')
    {
        if (saveptr == NULL || strlen(saveptr) == 0)
        {
            if (token[strlen(token) - 1] == '&')
            {
                amp_flag = 1;
                break;
            }
        }
        token = strtok_r(NULL, delim, &saveptr);
    }

    // amp_flag=1 -> all tokens bg
    // amp_flag=0 -> all except last tokens bg
    in_cpy = strdup(in);
    token = strtok_r(in, "&", &saveptr);
    while (token && token[0] != '\n')
    {
        char *tkcpy = strtok(strdup(token), delim);
        if (strcmp(tkcpy, "warp") == 0 || strcmp(tkcpy, "peek") == 0 || strcmp(tkcpy, "seek") == 0 || strcmp(tkcpy, "proclore") == 0 || strcmp(tkcpy, "ping") == 0 || strcmp(tkcpy, "pastevents") == 0 || strcmp(tkcpy, "help") == 0 || strcmp(tkcpy, "activities") == 0 || strcmp(tkcpy, "iMan") == 0 || strcmp(tkcpy, "fg") == 0 || strcmp(tkcpy, "bg") == 0 || strcmp(tkcpy, "exit") == 0)
        {
            token = strtok_r(in_cp2, "&", &saveptr);
            if (o_file != NULL)
            {
                if (app == 1)
                {
                    int fd = open(o_file, O_CREAT | O_WRONLY | O_APPEND, 0644);
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                }
                else
                {
                    int fd = open(o_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                }
            }
            if (i_file != NULL)
            {
                int fd1 = open(i_file, O_RDONLY, 0644);
                dup2(fd1, STDIN_FILENO);
                close(fd1);
            }
            AssignFunc(token, prev, home, fgprompt, Q, pastpath, in_global, head);
            dup2(stdin_bkp, STDIN_FILENO);
            dup2(stdout_bkp, STDOUT_FILENO);
        }
        else
        {
            token = strtok_r(in_cp3, "&", &saveptr);
            // printf("%s\n", token);
            if (amp_flag == 0)
            {
                if (saveptr == NULL || strlen(saveptr) == 0)
                {
                    double time = fg(token, prev, home, fgprompt, Q, pastpath, in_global, head, o_file, app, i_file);
                    if (time > 2)
                    {
                        char *t = strtok(in_cpy, delim);
                        int tim = (int)time;
                        char fgp[4096];
                        snprintf(fgp, sizeof(fgp), "%s : %d", t, tim);
                        *fgprompt = strdup(fgp);
                    }
                }
                else
                {
                    bg(token, prev, home, fgprompt, Q, head, pastpath, in_global, o_file, app, i_file);
                }
            }
            else
            {
                bg(token, prev, home, fgprompt, Q, head, pastpath, in_global, o_file, app, i_file);
            }
        }
        token = strtok_r(saveptr, "&", &saveptr);
    }
}

double fg(char *in, char **prev, const char *home, char **fgprompt, Que Q, char *pastpath, char *in_global, Node head, char *o_file, int app, char *i_file)
{
    struct timeval start, end;
    double elapsedTime;
    gettimeofday(&start, NULL);
    // printf("%s\n",in);
    int f = fork();
    if (f > 0)
    {
        head->pid = f;
        char *tok = strtok(strdup(in), "   \n\0\t");
        tok[0] = toupper(tok[0]);
        head->cmd = strdup(tok);
        LLAdd(activity, in, f);
        // printf("%d\n", f);
    }
    if (f == -1)
    {
        perror("fork");
        return -1;
    }
    else if (f > 0)
    {
        // parent
        int s;
        waitpid(f, &s, WUNTRACED);
    }
    else if (f == 0)
    {
        // child
        if (o_file != NULL)
        {
            if (app == 1)
            {
                int fd = open(o_file, O_CREAT | O_WRONLY | O_APPEND, 0644);
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }
            else
            {
                int fd = open(o_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }
        }
        if (i_file != NULL)
        {
            int fd1 = open(i_file, O_RDONLY, 0644);
            dup2(fd1, STDIN_FILENO);
            close(fd1);
        }
        // printf("Assign entered %s\n",in);
        AssignFunc(in, prev, home, fgprompt, Q, pastpath, in_global, head);
        // printf("Assign returned\n");
        dup2(stdin_bkp, STDIN_FILENO);
        dup2(stdout_bkp, STDOUT_FILENO);
        exit(1);
    }
    gettimeofday(&end, NULL);

    elapsedTime = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    // printf("Completed with %lf seconds.\n", elapsedTime);

    return elapsedTime;
}

void bg(char *in, char **prev, const char *home, char **fgprompt, Que Q, Node head, char *pastpath, char *in_global, char *o_file, int app, char *i_file)
{
    int f = fork();
    if (f == -1)
    {
        perror("fork");
        return;
    }
    else if (f > 0)
    {
        // parent
        LLAdd(activity, in, f);
        printf("%d\n", f);
        char *tok = strtok(strdup(in), "   \n\0\t");
        tok[0] = toupper(tok[0]);
        LLAdd(head, tok, f);
        return;
    }
    else if (f == 0)
    {
        // child
        if (app == 1)
        {
            int fd = open(o_file, O_CREAT | O_WRONLY | O_APPEND, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else
        {
            int fd = open(o_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        AssignFunc(in, prev, home, fgprompt, Q, pastpath, in_global, head);
        dup2(stdin_bkp, STDIN_FILENO);
        dup2(stdout_bkp, STDOUT_FILENO);
        exit(1);
    }
}