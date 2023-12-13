#include "headers.h"

char *path(const char *cwd, const char *home)
{
    if (strcmp(cwd, home) == 0)
    {
        return strdup("~");
    }
    else if (strlen(cwd) > strlen(home) && strncmp(cwd, home, strlen(home)) == 0)
    {
        char *path = (char *)malloc(strlen("~/") + strlen(cwd + strlen(home)) + 1);
        if (path != NULL)
        {
            sprintf(path, "~%s", cwd + strlen(home));
        }
        return path;
    }
    else
    {
        return strdup(cwd);
    }
}
void prompt(const char *home,char** fgprompt)
{
    int hostname_max_length = sysconf(_SC_HOST_NAME_MAX);
    char host[hostname_max_length];
    gethostname(host, hostname_max_length);
    char *Sys = getlogin();
    char *cwd = getcwd(NULL, 0);
    char *dir = path(cwd, home);
    printf(BOLD"<"CYAN"%s"RESET BOLD"@"MAGENTA"%s"RESET BOLD":""%s %s"">"RESET, Sys, host, dir,*fgprompt);
    // free(dir);
    // free(Sys);
    // free(cwd);
    *fgprompt="";
    return;
}