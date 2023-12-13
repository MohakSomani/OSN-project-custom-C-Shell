#include "headers.h"

int alphasort(const struct dirent **a, const struct dirent **b);

void peek(char *input, char **prev, const char *home)
{
    char delim[] = "   \t\n\0;";
    char *saveptr;
    char *token = strtok_r(input, delim, &saveptr);
    int a = 0, l = 0, f = 0;

    while (token != NULL && token[0] == '-')
    {
        f = 1;
        if (token[1] == '\0')
        {
            printf("No such file or directory\n");
            return;
        }

        int ln = strlen(token);
        for (int i = 1; i < ln; i++)
        {
            if (token[i] == 'a')
                a = 1;
            else if (token[i] == 'l')
                l = 1;
            else
            {
                printf("Invalid Flag\n");
                return;
            }
        }
        token = strtok_r(NULL, delim, &saveptr);
    }
    if (token == NULL)
    {
        token = getcwd(NULL, 0);
    }
    else if (strcmp(token, "~") == 0)
    {
        token = strdup(home);
    }
    else if (strncmp(token, "~/", 2) == 0)
    {
        token = strcat(strdup(home), token + 1);
    }
    struct dirent **namelist;

    int num_entries = scandir(token, &namelist, NULL, alphasort);
    if(num_entries==-1)
    {
        printf("Invalid Directory Entered.\n");
        return;
    }
    for (int i = 0; i < num_entries; ++i)
    {
        struct dirent *entry = namelist[i];
        if (a == 0)
        {
            if (strncmp(entry->d_name, ".", 1) == 0 || strncmp(entry->d_name, "..", 2) == 0)
                continue;
        }
        char file_path[1024];
        snprintf(file_path, sizeof(file_path), "%s/%s", token, entry->d_name);

        struct stat file_info;
        if (stat(file_path, &file_info) == -1)
        {

            printf("==ERROR IN GETTING FILE STATS==\n");
            continue;
        }
        mode_t mode = file_info.st_mode;
        if (l == 1)
        {
            struct passwd *pw = getpwuid(file_info.st_uid);
            struct group *grp = getgrgid(file_info.st_gid);
            struct tm *timeinfo = localtime(&file_info.st_mtime); // st_mtime stores the last modified time of the file

            char perms[10];
            perms[0] = (S_ISDIR(mode)) ? 'd' : '-';
            perms[1] = (mode & S_IRUSR) ? 'r' : '-';
            perms[2] = (mode & S_IWUSR) ? 'w' : '-';
            perms[3] = (mode & S_IXUSR) ? 'x' : '-';
            perms[4] = (mode & S_IRGRP) ? 'r' : '-';
            perms[5] = (mode & S_IWGRP) ? 'w' : '-';
            perms[6] = (mode & S_IXGRP) ? 'x' : '-';
            perms[7] = (mode & S_IROTH) ? 'r' : '-';
            perms[8] = (mode & S_IWOTH) ? 'w' : '-';
            perms[9] = (mode & S_IXOTH) ? 'x' : '-';
            perms[10] = '\0';

            printf("%-11s %2ld %-8s %-8s %8ld %.12s ",
                   perms,
                   file_info.st_nlink,
                   pw->pw_name,
                   grp->gr_name,
                   file_info.st_size,
                   ctime(&file_info.st_mtime) + 4); // Month Day Hour:Minute
            if (S_ISDIR(mode))
                printf("\033[1;34m%s\033[1;0m\n", entry->d_name);
            else if (mode & S_IXUSR)
            {
                printf("\033[1;32m%s\033[1;0m\n", entry->d_name);
            }
            else
            {
                printf("\033[1;37m%s\033[1;0m\n", entry->d_name);
            }
            free(entry);
        }
        else
        {
            if (S_ISDIR(mode))
                printf("\033[1;34m%-15s     \033[1;0m", entry->d_name);
            else if (mode & S_IXUSR)
            {
                printf("\033[1;32m%-15s     \033[1;0m", entry->d_name);
            }
            else
            {
                printf("\033[1;37m%-15s     \033[1;0m", entry->d_name);
            }
            if (i != 0 && i % 5 == 0)
                printf("\n");
        }
    }
    printf("\n");

    free(namelist);
}