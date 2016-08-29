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
#include <stdio.h>
#include <stdlib.h>
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void inorder_traversal(struct TreeNode *root, int **buf, int depth, int *buf_size, int *max_depth) {
    if (root == NULL) return;
    if (depth > *buf_size) {
        *buf_size <<= 1;
        *buf = (int *)realloc(*buf, sizeof(int) * (*buf_size));
    }
    if (depth > *max_depth) *max_depth = depth;

    if (root->left != NULL) inorder_traversal(root->left, buf, depth + 1, buf_size, max_depth);
    (*buf)[depth - 1] = root->val;
    if (root->right != NULL) inorder_traversal(root->right, buf, depth + 1, buf_size, max_depth);
}

int* rightSideView(struct TreeNode* root, int* returnSize) {
    int buf_size = 1024;
    int *buf = (int *)malloc(sizeof(int) * buf_size);
    *returnSize = 0;

    inorder_traversal(root, &buf, 1, &buf_size, returnSize);
    return buf;
}

int main() {
    struct TreeNode nodes[] = {
        {1, NULL, NULL},
        {2, NULL, NULL},
        {3, NULL, NULL}
    };

    int i, returnSize;

    nodes[0].left = &nodes[1];
    nodes[0].right = &nodes[2];

    int *result = rightSideView(&nodes[0], &returnSize);
    for (i = 0; i < returnSize; i++) {
        printf("%d\n", result[i]);
    }
    free(result);

}
