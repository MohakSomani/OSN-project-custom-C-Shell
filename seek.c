#include "headers.h"

int alphasort(const struct dirent **a, const struct dirent **b);

void seek(char *input, const char *home, char **prev)
{
    char delim[] = "   \t\n\0;";
    char *saveptr;
    char *token = strtok_r(input, delim, &saveptr);
    int d = 0, f = 0, e = 0;

    while (token != NULL && token[0] == '-')
    {
        int l = strlen(token);
        for (int i = 1; i < l; i++)
        {
            if (token[i] == 'd')
                d = 1;
            else if (token[i] == 'e')
                e = 1;
            else if (token[i] == 'f')
                f = 1;
            else
            {
                printf("Invalid Flag\n");
                return;
            }
        }
        token = strtok_r(NULL, delim, &saveptr);
    }
    if (d == 1 && f == 1)
    {
        printf("Invalid flags!\n");
        return;
    }
    char *target = strdup(token);
    char *dir_path;
    saveptr = strtok(saveptr, delim);
    if (saveptr == NULL || strcmp(saveptr, ".") == 0)
        dir_path = strdup(home);
    else if (strncmp(saveptr, "~/", 2) == 0)
    {
        dir_path = strcat(strdup(home), saveptr + 1);
    }
    else if (strncmp(saveptr, "./", 2) == 0)
    {
        dir_path = strcat(getcwd(NULL, 0), saveptr + 1);
    }
    else if (strcmp(saveptr, "..") == 0)
    {
        chdir("..");
        char *dotdot = getcwd(NULL, 0);
        chdir(home);
        dir_path = strdup(dotdot);
    }
    else if (strncmp(saveptr, "../", 3) == 0)
    {
        chdir("..");
        char *dotdot = getcwd(NULL, 0);
        chdir(home);
        dir_path = strcat(dotdot, saveptr + 2);
    }
    else
        dir_path = strdup(saveptr);
    int c = 0;
    char *pat;
    mode_t mod;
    char *f_name = strrchr(dir_path, '/');
    if (f_name != NULL)
    {
        if ((f_name + 1, ".", 1) == 0 || strncmp(f_name + 1, "..", 2) == 0)
        {
            printf("Invalid Directory(starting with '.' or '..')\n");
            return;
        }
    }
    seek_rec(target, dir_path, d, e, f, &c, &pat, &mod, home);
    if (c == 1 && e == 1)
    {
        if (S_ISDIR(mod))
        {
            chdir(pat);
        }
        else
        {
            FILE *file = fopen(pat, "r");
            if (file == NULL)
            {
                perror("Error opening the file");
                return;
            }

            int character;
            while ((character = fgetc(file)) != EOF)
            {
                putchar(character);
            }

            fclose(file);
        }
    }
}

void seek_rec(const char *target, char *dir_path, int d, int e, int f, int *c, char **pat, mode_t *mod, const char *home)
{
    struct dirent **namelist;

    int num_entries = scandir(dir_path, &namelist, NULL, alphasort);
    if (num_entries == -1)
    {
        printf("Invalid Directory Entered.\n");
        return;
    }
    for (int i = 0; i < num_entries; ++i)
    {
        struct dirent *entry = namelist[i];

        if (strncmp(entry->d_name, ".", 1) == 0 || strncmp(entry->d_name, "..", 2) == 0)
            continue;

        char file_path[1024];
        snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, entry->d_name);

        struct stat file_info;
        if (stat(file_path, &file_info) == -1)
        {

            printf("==ERROR IN GETTING FILE STATS==\n");
            continue;
        }
        mode_t mode = file_info.st_mode;
        if (S_ISDIR(mode))
        {
            seek_rec(target, file_path, d, e, f, c, pat, mod, home);
        }
        char *file_pat = path(file_path, home);
        if (strncmp(entry->d_name, target, strlen(target)) == 0)
        {
            if (S_ISDIR(mode) || entry->d_name[strlen(target)] == '.')
            {
                if (d == 1 && S_ISDIR(mode))
                {
                    *c = *c + 1;
                    *pat = strdup(file_path);
                    *mod = mode;
                    printf("\033[0;34m%s\n\033[0m", file_pat);
                }
                if (f == 1 && !S_ISDIR(mode))
                {
                    *c = *c + 1;
                    *pat = strdup(file_path);
                    *mod = mode;

                    printf("\033[0;32m%s\n\033[0m", file_pat);
                }
                if (d == 0 && f == 0)
                {
                    *c = *c + 1;
                    *pat = strdup(file_path);
                    *mod = mode;

                    if (S_ISDIR(mode))
                        printf("\033[0;34m%s\n\033[0m", file_pat);
                    else
                        printf("\033[0;32m%s\n\033[0m", file_pat);
                }
            }
        }
    }
}