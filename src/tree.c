#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

/* Implementation of the file system through a tree data structure */

// Function to create a new tree node
struct TreeNode* createNode(char* name, struct TreeNode* parent) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (newNode != NULL) {
        newNode->name = name;
        newNode->numChildren = 0;
        newNode->children = NULL;
        newNode->parent = parent;
    }
    return newNode;
}

// Function to add a child to a tree node with a unique name check
void addChild(struct TreeNode* parent, struct TreeNode* child) {
    // Check if the name is unique among children
    for (int i = 0; i < parent->numChildren; ++i) {
        if (strcmp(parent->children[i]->name, child->name) == 0) {
            fprintf(stderr, "Error: Name '%s' is not unique among children.\n", child->name);
            free(child->name);
            free(child);
            return;
        }
    }

    // Add the child if the name is unique
    parent->numChildren++;
    parent->children = (struct TreeNode**)realloc(parent->children, sizeof(struct TreeNode*) * parent->numChildren);
    parent->children[parent->numChildren - 1] = child;
    child->parent = parent;
}

// Function to perform a depth-first traversal of the tree
void depthFirstTraversal(struct TreeNode* root) {
    if (root != NULL) {
        printf("%s ", root->name);
        for (int i = 0; i < root->numChildren; ++i) {
            depthFirstTraversal(root->children[i]);
        }
    }
}

// Function to free the memory allocated for the tree nodes
void freeTree(struct TreeNode* root) {
    if (root != NULL) {
        for (int i = 0; i < root->numChildren; ++i) {
            freeTree(root->children[i]);
        }
        free(root->children);
        free(root);
    }
}

// Function to find the parent of a given node in a general tree
struct TreeNode* findParent(struct TreeNode* root, struct TreeNode* node) {
    if (root == NULL || node == NULL || root == node) {
        return NULL; // Invalid inputs or root is the same as the node
    }

    for (int i = 0; i < root->numChildren; ++i) {
        if (root->children[i] == node) {
            return root; // Current root is the parent of the target node
        }

        // Recursively search in the subtree
        struct TreeNode* result = findParent(root->children[i], node);
        if (result != NULL) {
            return result;
        }
    }

    return NULL; // Node not found in the subtree
}

// Function to print the tree nodes (for testing purposes)
void printTree(struct TreeNode* root, int depth) {
    if (root == NULL) {
        return;
    }

    for (int i = 0; i < depth; ++i) {
        printf("  "); // Indentation for better visualization
    }

    printf("%s\n", root->name);

    for (int i = 0; i < root->numChildren; ++i) {
        printTree(root->children[i], depth + 1);
    }
}