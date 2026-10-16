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
    int pre = 0;
    int post = 0;
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        return dfs(preorder, postorder);
    }
    TreeNode* dfs(vector<int>& preorder, vector<int>& postorder) {
        TreeNode* root = new TreeNode(preorder[pre++]);
        if (root->val != postorder[post])
            root->left = dfs(preorder, postorder);
        if (root->val != postorder[post])
            root->right = dfs(preorder, postorder);
        post++;
        return root;
    }
};