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
    vector<int> dfs(TreeNode* root) {
        if (!root->left && !root->right)
            return {1, 0, 0};

        if (!root->left || !root->right) {
            TreeNode* child;
            if (root->left) child = root->left;
            if (root->right) child = root->right;
            auto c = dfs(child);
            int ans0 = min(1 + c[1], 1 + c[2]);
            int ans1 = min(c[0], 1 + c[1]);
            int ans2 = c[1];
            return {ans0, ans1, ans2};
        }

        auto l = dfs(root->left);
        auto r = dfs(root->right);
        int ans0 = min(1 + l[1] + r[1], min(1 + l[2] + r[0], 1 + r[2] + l[0]));
        // ans0 = min(ans0, 1 + l[2] + 1 + r[2]);
        int ans1 = min(l[0] + r[0], 1 + l[1] + r[1]);
        int ans2 = l[1] + r[1];
        return {ans0, ans1, ans2};
    }
    int minCameraCover(TreeNode* root) {
        return dfs(root)[0];
    }
};