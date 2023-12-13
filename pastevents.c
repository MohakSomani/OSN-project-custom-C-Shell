#include "headers.h"

char *replaceSubstring(char *str, char *oldSubstr, char *newSubstr)
{
    char *pos = strstr(str, oldSubstr);

    if (pos != NULL)
    {
        int oldLen = strlen(oldSubstr);
        int newLen = strlen(newSubstr);
        int tailLen = strlen(pos + oldLen);

        memmove(pos + newLen, pos + oldLen, tailLen + 1);
        memcpy(pos, newSubstr, newLen);
        // printf("%s\n", newSubstr);
        // return newSubstr;
        // return str;
        int i = 0, c = 0;
        char *tmp = (char *)malloc(sizeof(char) * 4097);
        while (str[i] != '\0')
        {
            if (str[i] != '\n')
            {
                tmp[c++] = str[i];
            }
            i++;
        }
        tmp[c]='\0';

        // printf("%s\n", tmp);
        return tmp;
    }
}

void pastevent(char *input, char **prev, const char *home, char **fgprompt,Que Q,char* pastpath,char* in_global,Node head)
{

    char delim[] = "   \t\n\0";
    char *token = strtok(input, delim);
    // printf("token:%s\n", token);
    if (token == NULL)
    {
        PrintQue(Q);
    }
    else if (strcmp(token, "purge") == 0)
    {
        FILE *file = fopen(pastpath, "w");
        if (file == NULL)
        {
            perror("Error opening the file");
            return;
        }
        fclose(file);
        Q->start = 0;
        Q->end = -1;
        Q->numelems = 0;
    }
    else if (strcmp(token, "execute") == 0)
    {
        char *ts = strtok(NULL, delim);
        int t = atoi(ts);
        int id = (Q->end - t + 1) % 15;
        if (id < 0)
            id += 15;
        char *str = strdup(Q->arr[id]);
        char pe[] = "pastevents execute ";
        strcat(pe, ts);
        char *t1 = strdup(Q->arr[id]);
        t1[strlen(t1) - 1] = '\0';
        in_global = replaceSubstring(in_global, pe, t1);
        strcat(in_global, "\n");
        Enque(Q,in_global);
        token = strtok(str, ";");
        while (token)
        {
            pipe_handle(token, prev, home, fgprompt,Q,head,pastpath,in_global);
            // AssignFunc(token, prev, home);
            token = strtok(NULL, ";");
        }
    }

    // SaveEntries();
}