#include "headers.h"

void die(const char *s)
{
    perror(s);
    exit(1);
}
struct termios orig_termios;
void disableRawMode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}
void enableRawMode()
{
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}
// Boiler Plate end
void neonate(char *in)
{
    char *delim = "   \n\t\0";
    char *tok = strtok(in, delim);
    if (strcmp(tok, "-n") != 0)
    {
        return;
    }
    tok = strtok(NULL, delim);
    int n = atoi(tok);
    // printf("%d",n);
    char x = 'x';

    setbuf(stdout, NULL);
    enableRawMode();
    int f = fork();
    char* last_proc_path="/proc/sys/kernel/ns_last_pid";
    if (f == 0)
    {
        while (1)
        {

            FILE *f_ptr = fopen(last_proc_path, "r");
            char pid[10];
            fgets(pid, 10, f_ptr);

            printf("%s", pid);

            sleep(n);
        }
    }
    else if (f > 0)
    {
        int c;
        while ( ((c = getc(stdin)) != EOF) && (char)c != x && (char)c!=toupper(x))
        {
            continue;
        }

        kill(f, SIGKILL);
    }
    disableRawMode();
}