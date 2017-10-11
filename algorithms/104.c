/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

#define MAX(a, b) ((a) > (b) ? (a) : (b))
int maxDepth(struct TreeNode* root) {
    int left, right;

    if (root == NULL) return 0;
    if (root->left != NULL && root->right != NULL) {
		left = maxDepth(root->left);
		right = maxDepth(root->right);
	    return 1 + MAX(left, right);
	}

    if (root->left != NULL) return 1 + maxDepth(root->left);
    if (root->right != NULL) return 1 + maxDepth(root->right);
    return 1;
}
int main()
{
}
