#pragma once

// Define a structure for a tree node
struct TreeNode {
    char* name;
    struct TreeNode** children; // Array of child pointers
    int numChildren;            // Number of children
    struct TreeNode* parent;    // Pointer to the parent node
};

// Function Declarations
struct TreeNode* createNode(char* name, struct TreeNode* parent);
void addChild(struct TreeNode* parent, struct TreeNode* child);
void depthFirstTraversal(struct TreeNode* root);
void freeTree(struct TreeNode* root);
struct TreeNode* findParent(struct TreeNode* root, struct TreeNode* node);
void printTree(struct TreeNode* root, int depth);

