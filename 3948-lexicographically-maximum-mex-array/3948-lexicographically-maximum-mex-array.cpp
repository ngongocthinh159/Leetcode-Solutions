#define BIT 28
struct Node {
    Node* child[2];
    int cnt;
    int leaf;
    Node() {
        child[0] = child[1] = nullptr;
        cnt = 0;
        leaf = 0;
    }
};
struct Trie {
public:
    Trie() {
        root = new Node;
    }
    void insert(int x) {
        insert_dfs(root, x, BIT);
    }
    void remove(int x) {
        remove_dfs(root, x, BIT);
    }
    int queryMex() {
        Node* p = root;
        int res = 0;
        for (int bit = BIT; bit >= 0; bit--) {
            if (p->child[0] == nullptr) return res;
            if (p->child[0]->leaf < (1 << bit)) {
                p = p->child[0];
            } else {
                res = res | (1 << bit);
                if (p->child[1] == nullptr) return res;
                p = p->child[1];
            }
        }
        return res;
    }
private:
    Node* root;
    void insert_dfs(Node* root, int x, int bit) {
        root->cnt++;
        if (bit == -1) {
            root->leaf = 1;
            return;
        }
        int idx = (x >> bit) & 1;
        if (root->child[idx] == nullptr) root->child[idx] = new Node;
        insert_dfs(root->child[idx], x, bit - 1);
        root->leaf = 0;
        if (root->child[0]) root->leaf += root->child[0]->leaf;
        if (root->child[1]) root->leaf += root->child[1]->leaf;
    }
    void remove_dfs(Node* root, int x, int bit) {
        root->cnt--;
        if (bit == -1) {
            if (root->cnt == 0) root->leaf = 0;
            return;
        }
        int idx = (x >> bit) & 1;
        if (root->child[idx] != nullptr) remove_dfs(root->child[idx], x, bit - 1);
        root->leaf = 0;
        if (root->child[0]) root->leaf += root->child[0]->leaf;
        if (root->child[1]) root->leaf += root->child[1]->leaf;
    }
};
class Solution {
public:
    vector<int> maximumMEX(vector<int>& nums) {
        int n = nums.size();
        Trie tree;
        for (int i = 0; i < n; i++) tree.insert(nums[i]);
        vector<int> res;
        // cout << tree.queryMex() << '\n';
        int j = 0;
        while (j < n) {
            int mex = tree.queryMex();
            Trie tree2;
            tree2.insert(nums[j]);
            int start = j, end = j;
            j++;
            while (j < n && tree2.queryMex() != mex) {
                tree2.insert(nums[j]);
                end = j;
                j++;
            }
            // cout << "here" << '\n';
            res.push_back(mex);
            for (int k = start; k <= end; k++) tree.remove(nums[k]);
        }
        return res;
    }
};