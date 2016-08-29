/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize) {
    struct TreeNode *node;
    unsigned int i, offset;

    if (inorderSize <= 0) return NULL;
    if (inorderSize == 1) {
        node = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        node->left = NULL;
        node->right = NULL;
        node->val = inorder[0];
        return node;
    }

    node = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    node->val = postorder[postorderSize - 1];
    for (offset = 0; offset < inorderSize && inorder[offset] != node->val; offset++) ;
    node->left = buildTree(inorder, offset, postorder, offset);
    node->right = buildTree(inorder + offset + 1, inorderSize - offset - 1, postorder + offset, inorderSize - offset - 1);
    return node;
}

void pre_order_traversal(struct TreeNode *root) {
    if (root == NULL) return;
    printf("%d\n", root->val);
    if (root->left != NULL) pre_order_traversal(root->left);
    if (root->right != NULL) pre_order_traversal(root->right);
    free(root);
}

int main() {
    int inorder[] = {1, 3, 2}, postorder[] = {3, 2, 1};
    struct TreeNode *result = buildTree(inorder, 3, postorder, 3);
    pre_order_traversal(result);
    return 0;
}
