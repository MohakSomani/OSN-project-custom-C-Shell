#include <stdio.h>

void help() {
    // Define color codes
    const char* RED = "\033[0;31m";
    const char* GREEN = "\033[0;32m";
    const char* YELLOW = "\033[0;33m";
    const char* BLUE = "\033[0;34m";
    const char* MAGENTA = "\033[0;35m";
    const char* CYAN = "\033[0;36m";
    const char* RESET = "\033[0m";

    printf("%sCustom C-Shell Help%s\n", MAGENTA, RESET);
    printf("%s===================%s\n", MAGENTA, RESET);
    printf("This shell is a Unix-like command-line interface that replicates and extends traditional shell capabilities with various custom features.\n\n");

    printf("%sUser-Implemented Commands:%s\n\n", CYAN, RESET);

    // Warp command
    printf("%swarp (cd):%s\n", GREEN, RESET);
    printf("  The '%swarp%s' command is an enhanced version of '%scd%s', allowing you to navigate directories using absolute or relative paths.\n", BLUE, RESET, BLUE, RESET);
    printf("  It supports flags like %s~%s, %s..%s, %s.%s, and %s-%s for easier directory traversal.\n\n", YELLOW, RESET, YELLOW, RESET, YELLOW, RESET, YELLOW, RESET);

    // Peek command
    printf("%speek (ls):%s\n", GREEN, RESET);
    printf("  The '%speek%s' command lists files and directories in lexicographic order.\n", BLUE, RESET);
    printf("  It supports flags like %s-l%s for detailed info and %s-a%s for displaying hidden files.\n\n", YELLOW, RESET, YELLOW, RESET);

    // Seek command
    printf("%sseek (find):%s\n", GREEN, RESET);
    printf("  The '%sseek%s' command searches for files or directories in the specified or current directory.\n", BLUE, RESET);
    printf("  Flags like %s-d%s, %s-f%s, and %s-e%s refine search results based on file types.\n\n", YELLOW, RESET, YELLOW, RESET, YELLOW, RESET);

    // Past Events (history) command
    printf("%spastevents (history):%s\n", GREEN, RESET);
    printf("  The '%spastevents%s' command shows your command history, helping you review past actions and troubleshoot.\n", BLUE, RESET);
    printf("  You can also clear history with '%spurge%s' or rerun specific commands using their index.\n\n", YELLOW, RESET);

    // Process and Job Management commands
    printf("%sForeground and Background Processes:%s\n", GREEN, RESET);
    printf("  You can run commands in the foreground or background using '%s&%s' for background processes.\n\n", YELLOW, RESET);
    
    printf("%sproclore:%s\n", GREEN, RESET);
    printf("  Prints process-related information for the shell program.\n\n");
    
    printf("%sactivities:%s\n", GREEN, RESET);
    printf("  Lists all currently running jobs, especially background jobs, in their creation order.\n\n");

    printf("%sping <jobNumber> <signalNumber>:%s\n", GREEN, RESET);
    printf("  Sends a signal to a running job by its job number.\n\n");

    printf("%sfg <jobNumber>:%s\n", GREEN, RESET);
    printf("  Brings a background job to the foreground.\n\n");

    printf("%sbg <jobNumber>:%s\n", GREEN, RESET);
    printf("  Starts a stopped job in the background.\n\n");

    // iMan command
    printf("%siMan:%s\n", GREEN, RESET);
    printf("  The '%siMan%s' command provides manual pages for commands, offering detailed usage information.\n\n", BLUE, RESET);

    // Neonate command
    printf("%sneonate:%s\n", GREEN, RESET);
    printf("  The '%sneonate%s' command allows users to create and execute custom scripts, simplifying repetitive tasks.\n\n", BLUE, RESET);

    // Help command
    printf("%shelp:%s\n", GREEN, RESET);
    printf("  The '%shelp%s' command provides an overview of all available commands and their functions.\n\n", BLUE, RESET);

    // Exit command
    printf("%sexit:%s\n", GREEN, RESET);
    printf("  Use '%sexit%s' to leave the shell.\n\n", BLUE, RESET);

    // Additional Commands
    printf("%sAdditional Commands:%s\n", CYAN, RESET);
    printf("  %sCTRL-Z:%s Stops the current job and pushes it to the background.\n", YELLOW, RESET);
    printf("  %sCTRL-D:%s Exits the shell if the prompt is empty.\n", YELLOW, RESET);
    printf("  %sCTRL-C:%s Cancels the current running command, similar to bash.\n", YELLOW, RESET);

    printf("\nThis shell replica is designed to offer a robust command-line environment with extended capabilities beyond traditional Unix-like systems.\n");
}
