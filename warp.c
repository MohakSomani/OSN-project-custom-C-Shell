#include "headers.h"

void warp(char *input, char **prev, const char *home, int f)
{
    // printf("\nwarp() Called\n");

    char delim[] = "   \t\n\0";
    char *saveptr;
    char *token = strtok_r(input, delim, &saveptr);
    if (token == NULL)
    {
        chdir(home);
        char *pwd = getcwd(NULL, 0);
        printf("%s\n", pwd);
        free(pwd);
    }
    else
    {
        while (token)
        {

            if (strcmp(token, "-") == 0)
            {
                if (*prev == NULL)
                {
                    printf("warp: Old PWD not set\n");
                }
                else
                {
                    char *tmp = getcwd(NULL, 0);
                    chdir(*prev);
                    *prev = tmp;
                    char *pwd = getcwd(NULL, 0);
                    printf("%s\n", pwd);
                    free(pwd);
                }
            }
            else if (strcmp(token, "~") == 0)
            {
                char *tmp = getcwd(NULL, 0);
                chdir(home);
                *prev = tmp;
                char *pwd = getcwd(NULL, 0);
                printf("%s\n", pwd);
                free(pwd);
            }
            else if (strncmp(token, "~/", 2) == 0)
            {
                char *hm = strdup(home);
                strcat(hm, token + 1);
                char *tmp = getcwd(NULL, 0);

                chdir(hm);
                *prev = tmp;
                char *pwd = getcwd(NULL, 0);
                printf("%s\n", pwd);
                free(pwd);
            }
            else
            {

                char newpath[3 + strlen(token)];
                strcpy(newpath, "./");
                strcat(newpath, token);
                char *tmp = getcwd(NULL, 0);

                if (chdir(newpath) != 0)
                {
                    perror("warp");
                    // Print the specific error message using errno
                    // if (errno == ENOENT)
                    // {
                    //     printf("Directory does not exist.\n");
                    // }
                }
                else
                {
                    *prev = tmp;
                    if (f == 1)
                    {
                        char *pwd = getcwd(NULL, 0);
                        printf("%s\n", pwd);
                        free(pwd);
                    }
                }
            }
            token = strtok_r(NULL, delim, &saveptr);
        }
    }
}