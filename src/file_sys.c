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
    if (arg == NULL) {
        *current = root;
    }
    else if (strcmp(arg, "..") == 0) {
        *current = (*current)->parent;
    } else {
        struct TreeNode* child = childWithNameExists(*current, arg);
        if (child != NULL) {
            *current = child;
        } else {
            fprintf(stderr, "Error: Directory '%s' doesn't exist\n", arg);
        }
    }
}

void ls(struct TreeNode* current) {
    printChildren(current);
}


void mkdir(struct TreeNode** current, char** args) {
    char* arg = args[1];

    if (arg == NULL) {
        fprintf(stderr, "Error: Missing argument\n");
        return;
    }

    // Create a new directory and add it as a child
    struct TreeNode* child = createNode(arg, *current, 1);
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

void touch(struct TreeNode** current, char** args) {
    char* arg = args[1];

    if (arg == NULL) {
        fprintf(stderr, "Error: Missing argument\n");
        return;
    }

    // Create a new file
    FILE *file;
    char path[50] = "mnt/";
    strcat(path, arg); // concatenate string
    file = fopen(path, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not create the file.\n");
        return;
    }
    fclose(file);

    // Create child in tree
    struct TreeNode* child = createNode(arg, *current, 0);
    addChild(*current, child);
}