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
    int ans = INT_MIN;
    int dfs1(TreeNode* root) {
        if (!root) return 0;
        int l = dfs1(root->left);
        int r = dfs1(root->right);
        ans = max(ans, root->val + l + r);
        ans = max(ans, root->val + max(0, max(l, r)));
        return root->val + max(0, max(l, r));
    }
    int maxPathSum(TreeNode* root) {
        dfs1(root);
        return ans;
    }
};