#include "headers.h"

// head data is not counted .. Head is a dummy node

Node LLAdd(Node head, char *cmd, pid_t pid)
{
    Node L = head;
    Node p = head;
    while (L->next != NULL && pid > L->pid)
    {
        p = L;
        L = L->next;
    }
    Node tmp = p->next;
    p->next = (Node)malloc(sizeof(struct node));
    p->next->cmd = cmd;
    p->next->pid = pid;
    p->next->next = tmp;
    return p->next;
}

void Delete(Node prev)
{
    Node temp = prev->next->next;
    free(prev->next);
    prev->next = temp;
}

void Deletepid(Node head, int pid)
{
    Node L = head->next;
    Node p = head;
    while (L != NULL)
    {
        if (L->pid == pid)
        {
            Delete(p);
            return;
        }
        p=L;
        L=L->next;
    }
}

void CheckCompleted(Node head)
{
    Node L = head->next;
    Node prev = head;
    while (L != NULL)
    {
        int status;
        pid_t child_pid = waitpid(L->pid, &status, WNOHANG);
        if (child_pid == -1)
        {
            perror("fork");
            return;
        }
        if (child_pid != 0)
        {
            if (WIFEXITED(status))
            {
                printf("%s (%d) has completed normally with exit status: %d\n", L->cmd, child_pid, WEXITSTATUS(status));
                Delete(prev);
            }
            else if (WIFSIGNALED(status))
            {
                printf("%s (%d) was terminated by signal: %d\n", L->cmd, child_pid, WTERMSIG(status));
                Delete(prev);
            }
        }
        prev = L;
        L = L->next;
    }
}

void deleteLinkedList(Node head)
{
    if (head == NULL)
        return;
    deleteLinkedList(head->next);
    free(head);
    head = NULL;
}