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
    TreeNode* ans = nullptr;
    int mxd = -1;
    int dfs(TreeNode* root, int d) {
        if (!root) return d;
        int l = dfs(root->left, d + 1);
        int r = dfs(root->right, d + 1);
        if (l == r && mxd <= l) mxd = l, ans = root;
        return max(l, r);
    }
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        dfs(root, 0);
        return ans;
    }
};