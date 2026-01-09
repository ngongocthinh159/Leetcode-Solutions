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
    int first, last;
    TreeNode* ans = nullptr;
    int mxd = -1;
    void dfs(TreeNode* root, int d) {
        if (!root) return;
        if (mxd < d) {
            mxd = d;
            first = last = root->val;
        } else if (mxd == d) {
            last = root->val;
        }
        dfs(root->left, d + 1);
        dfs(root->right, d + 1);
    }
    pair<bool,bool> dfs2(TreeNode* root) {
        if (!root) return {false, false};
        auto l = dfs2(root->left);
        auto r = dfs2(root->right);
        pair<bool,bool> res = {l.first || r.first || root->val == first, l.second || r.second || root->val == last};
        if (res.first && res.second && !ans) ans = root;
        return res;
    }
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        dfs(root, 0);
        dfs2(root);
        return ans;
    }
};