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
#define N 100005
TreeNode* buf[N];
int top = 0;
class Solution {
public:
    void dfs(TreeNode* root) {
        if (!root) return;
        dfs(root->left);
        buf[top++] = root;
        dfs(root->right);
    }
    TreeNode* dnc(int l, int r) {
        if (l > r) return nullptr;
        int m = (l + r) / 2;
        TreeNode* res = buf[m];
        res->left = dnc(l, m - 1);
        res->right = dnc(m + 1, r);
        return res;
    }
    TreeNode* balanceBST(TreeNode* root) {
        top = 0;
        dfs(root);
        return dnc(0, top - 1);
    }
};