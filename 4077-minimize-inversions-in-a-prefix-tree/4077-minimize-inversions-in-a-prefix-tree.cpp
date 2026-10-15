#define B 10
int dp[1 << B];
int ans[B][B];
struct Node {
    Node *child[B];
    int val;
    Node() {
        for (int i = 0; i < B; i++) child[i] = nullptr;
        val = -1;
    }
};
class Solution {
public:
    void insert(Node *root, string &s, int x) {
        Node *p = root;
        int idx;
        for (auto c : s) {
            idx = c - 'a';
            if (!p->child[idx]) p->child[idx] = new Node();
            p = p->child[idx];
        }
        p->val = x;
    }
    int cal(vector<int>& a, vector<int>& b) {
        int res = 0;
        for (int i = int(a.size()) - 1, j = int(b.size()) - 1; i >= 0; --i) {
            while (j >= 0 && b[j] >= a[i]) j--;
            res += j + 1;
        }
        return res;
    }
    pair<vector<int>, int> dfs(Node *root) {
        if (!root) return make_pair(vector<int>(), 0);

        int cnt = 0;
        vector<int> curList;
        vector<vector<int>> cLists;
        for (int i = 0; i < B; ++i) if (root->child[i]) {
            auto [cList, cCnt] = dfs(root->child[i]);
            curList.insert(curList.end(), cList.begin(), cList.end());
            cLists.push_back(move(cList));
            cnt += cCnt;
        }
        int sz = cLists.size();
        for (int i = 0; i < sz; ++i)
            for (int j = 0; j < sz; ++j) if (i != j) ans[i][j] = cal(cLists[i], cLists[j]);
        for (int i = 0; i < (1 << sz); i++) dp[i] = INT_MAX;
        dp[0] = 0;
        for (int mask = 0; mask < (1 << sz); ++mask) {
            for (int j = 0; j < sz; ++j) if (!((mask >> j) & 1)) {
                int cost = 0;
                for (int i = 0; i < sz; ++i) if (((mask >> i) & 1) && i != j) cost += ans[i][j];
                dp[mask | (1 << j)] = min(dp[mask | (1 << j)], dp[mask] + cost);
            }
        }
        cnt += dp[(1 << sz) - 1];
        if (root->val != -1) {
            for (int i = 0; i < int(curList.size()); ++i) if (curList[i] < root->val) cnt++;
            curList.push_back(root->val);
        }
        sort(curList.begin(), curList.end());
        return make_pair(curList, cnt);
    }
    int minInversions(vector<string>& words, vector<int>& target) {
        int n = words.size();
        Node* root = new Node();
        vector<int> value(n);
        for (int i = 0; i < n; ++i) value[target[i]] = i;
        for (int i = 0; i < n; ++i) insert(root, words[i], value[i]);
        auto [list, res] = dfs(root);
        return res;
    }
};