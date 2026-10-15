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
    void dfs(TreeNode* root, unordered_map<int,int> &f, unordered_map<int,int> &g, vector<int> &preorder, vector<int>& postorder, int l1, int r1, int l2, int r2) {
        if (l1 == r1) return;
        
        if (preorder[l1 + 1] == postorder[r2 - 1]) {
            root->left = new TreeNode();
            root->left->val = preorder[l1 + 1];
            dfs(root->left, f, g, preorder, postorder, l1 + 1, r1, l2, r2 - 1);
        } else {
            root->left = new TreeNode();
            root->left->val = preorder[l1 + 1];
            dfs(root->left, f, g, preorder, postorder, l1 + 1, f[postorder[r2 - 1]] - 1, l2, g[preorder[l1 + 1]]);

            root->right = new TreeNode();
            root->right->val = postorder[r2 - 1];
            dfs(root->right, f, g, preorder, postorder, f[postorder[r2 - 1]], r1, g[preorder[l1 + 1]] + 1, r2 - 1);
        }
    }
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        TreeNode* root = new TreeNode;
        root->val = preorder[0];
        int n = preorder.size();
        unordered_map<int,int> f, g;
        for (int i = 0; i < n; i++) f[preorder[i]] = i;
        for (int i = 0; i < n; i++) g[postorder[i]] = i;
        dfs(root, f, g, preorder, postorder, 0, n - 1, 0, n - 1);
        return root;
    }
};