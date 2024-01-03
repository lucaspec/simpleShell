#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to prepend ".cmds/bin/" to a string
char* makeExecutable(const char *cmd) {
    // Assuming a reasonable maximum buffer size
    char prefix[] = "./cmds/bin/";

    // Allocate memory for the result string
    char *output = (char *)malloc(strlen(prefix) + strlen(cmd) + 1);

    // Check if memory allocation is successful
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Copy the prefix and concatenate the input string to the output buffer
    strcpy(output, prefix);
    strcat(output, cmd);

    return output;
}

