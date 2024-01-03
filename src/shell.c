#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "utils.h"

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 64

void readCommand(char* command) {
    printf(">> ");
    fgets(command, MAX_INPUT_SIZE, stdin);

    // Remove the trailing newline character
    size_t length = strlen(command);
    if (length > 0 && command[length - 1] == '\n') {
        command[length - 1] = '\0';
    }
}

void parseCommand(char* command, char** args) {
    // Initialize a pointer to the first token in the command
    char* token = strtok(command, " ");
    int i = 0;

    // Iterate through the tokens until there are no more or the maximum argument limit is reached
    while (token != NULL && i < MAX_ARG_SIZE - 1) {
        // Store the token in the args array
        args[i++] = token;

        // Move to the next token (NULL for subsequent calls on the same string)
        token = strtok(NULL, " ");
    }

    // Set the last element in the args array to NULL to signify the end of arguments
    args[i] = NULL;
}

int executeCommand(char** args) {
    // Create a child process
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {  // Code executed by the child process
        if (execvp(makeExecutable(args[0]), args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {  // Code executed by the parent process
        int status;

        // Wait for the child process to complete
        waitpid(pid, &status, 0);

        // Return the exit status of the child process
        return WEXITSTATUS(status);
    }

    // This line should never be reached
    return -1;
}

int main() {
    char input[MAX_INPUT_SIZE]; 
    char* args[MAX_ARG_SIZE]; // format: cmd arg1 arg2 arg3...
    

    while (1) {
        readCommand(input);

        if (strcmp(input, "exit") == 0) {
            printf("Exiting the shell. Goodbye!\n");
            break;
        }

        parseCommand(input, args);
        if (args[0] != NULL) {
            int status = executeCommand(args);
            if (status != 0) {
                fprintf(stderr, "Command failed with exit code %d\n", status);
            }
        }
    }

    return 0;
}
