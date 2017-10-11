 struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
 };
#include <stdio.h>
#include <stdlib.h>
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
void _sum(struct TreeNode *root, int left, int *sum)
{
    if (root == NULL) return;
    if (root->left == NULL && root->right == NULL && left) {
        *sum += root->val;
    }
    _sum(root->left, 1, sum);
    _sum(root->right, 0, sum);
}
int sumOfLeftLeaves(struct TreeNode* root)
{
    int ret = 0;
    _sum(root, 0, &ret);

    return ret;
}

int main()
{
}
