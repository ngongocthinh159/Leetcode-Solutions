
class Solution  {
public:
    struct node {
        node* child[26];
        int mnLength;
        int idx;
        node() {
            for (int i = 0; i < 26; i++) child[i] = nullptr;
            mnLength = INT_MAX;
            idx = -1;
        }
    };
    void insert(node *root, string &s, int cidx) {
        int len = s.size();
        node *p = root;
        if (len < p->mnLength) {
            p->mnLength = len;
            p->idx = cidx;
        }
        int idx;
        for (auto c : s) {
            idx = c - 'a';
            if (p->child[idx] == nullptr) p->child[idx] = new node;
            p = p->child[idx];
            if (len < p->mnLength) {
                p->mnLength = len;
                p->idx = cidx;
            }
        }
    }
    int query(node *root, string &s) {
        node* p = root;
        int idx;
        for (auto c : s) {
            idx = c - 'a';
            if (p->child[idx] == nullptr) return p->idx;
            p = p->child[idx];
        }
        return p->idx;
    }
    void deleteTrie(node *root) {
        if (root == nullptr) return;
        for (int i = 0; i < 26; i++) deleteTrie(root->child[i]);
        delete(root);
    }
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        node *root = new node;
        int idx = 0;
        for (auto &s : wordsContainer) {
            reverse(s.begin(), s.end());
            insert(root, s, idx++);
        }
        vector<int> ans(wordsQuery.size());
        for (int i = 0; i < int(wordsQuery.size()); i++) {
            reverse(wordsQuery[i].begin(), wordsQuery[i].end());
            ans[i] = query(root, wordsQuery[i]);
        }
        deleteTrie(root);
        return ans;
    }
};