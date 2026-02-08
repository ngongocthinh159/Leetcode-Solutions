/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool ans = true;
    int dfs(TreeNode *root, int d) {
        if (!root) return d;
        int l = dfs(root->left, d + 1);
        int r = dfs(root->right, d + 1);
        if (abs(l - r) >= 2) ans = false;
        return max(l, r);
    }
    bool isBalanced(TreeNode* root) {
        dfs(root, 0);
        return ans;
    }
};