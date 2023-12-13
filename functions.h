#ifndef __FUNC_H
#define __FUNC_H

void exit_handler(Que Q, char *pastpath);
void Ctrl_C_handler(int signal);
void Ctrl_D_handler(int signal);
void Ctrl_Z_handler(int signal);
void prompt(const char *home, char **fgprompt);
char *path(const char *cwd, const char *home);
void pipe_handle(char *in, char **prev, const char *home, char **fgprompt, Que Q, Node head, char *pastpath, char *in_global);
void fgbg_assign(char *in, char **prev, const char *home, char **fgprompt, Que Q, Node head, char *pastpath, char *in_global);
double fg(char *in, char **prev, const char *home, char **fgprompt, Que Q, char *pastpath, char *in_global, Node head, char *o_file, int app, char *i_file);
void bg(char *in, char **prev, const char *home, char **fgprompt, Que Q, Node head, char *pastpath, char *in_global, char *o_file, int app, char *i_file);
int AssignFunc(char *input, char **prev, const char *home, char **fgprompt, Que Q, char *pastpath, char *in_global, Node head);
void warp(char *input, char **prev, const char *home, int f);
void peek(char *input, char **prev, const char *home);
void proclore(char *input, const char *home);
void pastevent(char *input, char **prev, const char *home, char **fgprompt, Que Q, char *pastpath, char *in_global, Node head);
void seek(char *input, const char *home, char **prev);
void seek_rec(const char *target, char *dir_path, int d, int e, int f, int *c, char **path, mode_t *mod, const char *home);
char *replaceSubstring(char *str, char *oldSubstr, char *newSubstr);
void activities();
void neonate(char *in);
void iman(char *in);
void send_fg(char *in);
void send_bg(char *in);
void help();
void ping(char *input);

// LinkedList
Node LLAdd(Node head, char *cmd, pid_t pid);
void Delete(Node prev);
void CheckCompleted(Node head);
void deleteLinkedList(Node head);
void Deletepid(Node head, int pid);

    // Queue
    void Enque(Que Q, char *in);
void PrintQue(Que Q);
void SaveEntries(Que Q, char *pastpath);
void RetrieveQue(Que Q, char *pastpath);

#endif