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
    unordered_map<int,int> preIdx;
    unordered_map<int,int> postIdx;
    vector<int> preorder;
    vector<int> postorder;
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
        int n = pre.size();
        for (int i = 0; i < int(pre.size()); i++) preIdx[pre[i]] = i;
        for (int i = 0; i < int(post.size()); i++) postIdx[post[i]] = i;
        preorder = pre;
        postorder = post;
        return dfs(0, n - 1, 0, n - 1);
    }
    TreeNode* dfs(int l1, int r1, int l2, int r2) {
        TreeNode* root = new TreeNode(preorder[l1]);
        if (l1 == r1) return root;
        if (preorder[l1 + 1] == postorder[r2 - 1]) {
            root->left = dfs(l1 + 1, r1, l2, r2 - 1);
        } else {
            int rIdx = preIdx[postorder[r2 - 1]];
            root->left = dfs(l1 + 1, rIdx - 1, l2, postIdx[preorder[l1 + 1]]);
            root->right = dfs(rIdx, r1, postIdx[preorder[l1 + 1]] + 1, r2 - 1);
        }

        return root;
    }
};