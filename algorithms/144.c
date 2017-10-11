#include <stdlib.h>
#include <stdio.h>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

#define INITIAL_ARRAY_SIZE 1024 
struct array {
    int *data;
    unsigned int size;
    unsigned int offset;
};

struct array *array_create()
{
    struct array *arr = (struct array *)malloc(sizeof(struct array));
    arr->data = (int *)malloc(sizeof(int) * INITIAL_ARRAY_SIZE);
    arr->size = INITIAL_ARRAY_SIZE;
    arr->offset = 0;

    return arr;
}

void preorderTraversalFull(struct TreeNode* root, struct array *arr)
{

    if (arr->offset >= arr->size) {
        arr->size = arr->size << 1;
        arr->data = (int *)realloc(arr->data, arr->size * sizeof(int));
    }

    arr->data[arr->offset++] = root->val;

    if (root->left != NULL) preorderTraversalFull(root->left, arr);
    if (root->right != NULL) preorderTraversalFull(root->right, arr);
}

int* preorderTraversal(struct TreeNode* root, int* returnSize)
{
    struct array *arr = array_create();

    if (root != NULL) preorderTraversalFull(root, arr);
    *returnSize = arr->offset;
    return arr->data;
}





