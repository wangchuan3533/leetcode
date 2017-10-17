/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
#include <cstdio>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    // inplace invert
    TreeNode* invertTree(TreeNode* root) {
        if (root == NULL) return NULL;

        if (root->left == NULL && root->right == NULL) return root;

        if (root->left != NULL) invertTree(root->left);
        if (root->right != NULL) invertTree(root->right);

        // swap left and right sub-tree
        TreeNode *tmp = root->left;
        root->left = root->right;
        root->right = tmp;
        return root;
    }
};
