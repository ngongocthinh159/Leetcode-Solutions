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
    const int SEN = 1e5;
    tuple<int,int,bool,int,int> dfs(TreeNode* root) {
        if (!root) return {0,0,1,SEN,SEN};
        int l0,l1,r0,r1,lmn,lmx,rmn,rmx;
        bool l2, r2;
        tie(l0,l1,l2,lmn,lmx) = dfs(root->left);
        tie(r0,r1,r2,rmn,rmx) = dfs(root->right);
        if (lmn == SEN) lmn = INT_MAX;
        if (lmx == SEN) lmx = INT_MIN;
        if (rmn == SEN) rmn = INT_MAX;
        if (rmx == SEN) rmx = INT_MIN;
        int lval = !root->left ? INT_MIN : root->left->val;
        int rval = !root->right ? INT_MAX : root->right->val;
        bool ans3 = l2 && r2 && root->val > lmx && root->val < rmn;
        int ans2 = max(l1, max(r1, !ans3 ? 0 : root->val + l0 + r0));
        int ans4 = min(lmn, min(rmn, root->val));
        int ans5 = max(lmx, max(rmx, root->val));
        return {root->val + l0 + r0, ans2, ans3, ans4, ans5};
    }
    int maxSumBST(TreeNode* root) {
        return get<1>(dfs(root));
    }
};