#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

#define GREEN   "\x1B[32m"
#define BLUE    "\x1B[34m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"
#define BRIGHT_GREEN   "\x1B[92m"
#define BRIGHT_BLUE    "\x1B[94m"
#define BRIGHT_CYAN    "\x1B[96m"
#define BRIGHT_WHITE   "\x1B[97m"
#define RESET "\x1B[0m"


void cd(struct TreeNode** current, struct TreeNode* root, char** args) {
    char* arg = args[1];
    if (strcmp(arg, "..") == 0) {
        *current = (*current)->parent;
    } else {
        struct TreeNode* child = childWithNameExists(*current, arg);
        if (child != NULL) {
            *current = child;
        } else {
            fprintf(stderr, "Directory '%s' doesn't exist\n", arg);
        }
    }
}

void ls(struct TreeNode* current) {
    printChildren(current);
}


void mkdir(struct TreeNode** current, char** args) {
    char* arg = args[1];

    // Create a new directory and add it as a child
    struct TreeNode* child = createNode(arg, *current);
    addChild(*current, child);
}


void pwd(struct TreeNode* current) {
    char** dir = (char**)malloc(sizeof(char*));
    int dir_len = 0;

    // Store the current directory name
    dir = (char**)realloc(dir, sizeof(char*) * (dir_len + 1));
    dir[dir_len++] = current->name;

    // Store all parent directory names
    while (current->parent != NULL) {
        dir = (char**)realloc(dir, sizeof(char*) * (dir_len + 1));
        dir[dir_len++] = current->parent->name;
        current = current->parent;
    }

    // Parse full directory name
    printf("%s", CYAN);
    for (int i = dir_len - 1; i >= 0; i--) {
        printf("/%s", dir[i]);
    }
    printf("%s ", RESET);

    // Free allocated memory
    free(dir);
}

void tree(struct TreeNode* root) {
    printTree(root, 0);
}