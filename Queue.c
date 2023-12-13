#include "headers.h"

void Enque(Que Q,char *in)
{
    if (strstr(in, "pastevents") != NULL)
    {
        return;
    }
    if (Q->end >= 0 && strcmp(Q->arr[Q->end], in) == 0)
    {
        return;
    }
    if (Q->numelems < 15)
    {
        Q->end = (Q->end + 1) % 15;
        Q->arr[Q->end] = strdup(in);
        Q->numelems++;
    }
    else
    {
        Q->end = (Q->end + 1) % 15;
        Q->arr[Q->end] = strdup(in);
        Q->start = (Q->start + 1) % 15;
    }
}

void PrintQue(Que Q)
{
    for (int i = 0; i < Q->numelems; i++)
    {
        printf("%s", Q->arr[(Q->start + i) % 15]);
    }
    // printf("QUE PRINTED..\n");
}

void SaveEntries(Que Q,char* pastpath)
{
    // printf("SaveEntries:\nstart:%d , end:%d , numlines:%d\n",Q->start,Q->end,Q->numelems);
    // PrintQue();
    FILE *f = fopen(pastpath, "w");
    if (f == NULL)
    {
        perror("Error opening the file");
        return;
    }

    int i = Q->start;
    for (int i = 0; i < Q->numelems; i++)
    {
        if (fputs(Q->arr[(Q->start + i) % 15], f) <= 0)
        {
            printf("Error in printing to file\n");
        }
    }

    fclose(f);
    Q->start = 0;
    Q->end = -1;
    Q->numelems = 0;
}

void RetrieveQue(Que Q,char* pastpath)
{

    for (int i = 0; i < Q->numelems; i++)
    {
        Q->arr[(Q->start + i) % 15]="\0";
    }
    Q->start = 0;
    Q->end = -1;
    Q->numelems = 0;
    FILE *f = fopen(pastpath, "r");
    if(f==NULL)
    {
        perror("fopen");
        return ;
    }
    char input[4096];
    while (fgets(input, 4096, f))
    {
        Enque(Q,input);
    }
    fclose(f);
}