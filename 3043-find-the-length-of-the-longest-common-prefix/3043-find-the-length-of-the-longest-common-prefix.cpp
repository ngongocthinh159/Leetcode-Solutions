struct node {
    node *child[10];
    node() {
        for (int i = 0; i < 10; i++) child[i] = nullptr;
    }
};
class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        int n = arr1.size();
        int m = arr2.size();
        node* root = new node();
        for (int i = 0; i < n; i++) {
            node *p = root;
            int idx;
            string s = to_string(arr1[i]);
            for (auto c : s) {
                idx = c - '0';
                if (p->child[idx] == nullptr) p->child[idx] = new node();
                p = p->child[idx];
            }
        }
        int ans = 0;
        for (int i = 0; i < m; i++) {
            node *p = root;
            int idx, cnt = 0;
            string s = to_string(arr2[i]);
            for (auto c : s) {
                idx = c - '0';
                if (p->child[idx] == nullptr) break;
                p = p->child[idx];
                cnt++;
            }
            ans = max(ans, cnt);
        }
        return ans;
    }
};