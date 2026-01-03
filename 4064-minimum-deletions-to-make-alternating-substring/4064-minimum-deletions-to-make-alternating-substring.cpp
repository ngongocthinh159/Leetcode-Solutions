struct FenwickTree {
    vector<int> bit;  // binary indexed tree
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(vector<int> const &a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};
class Solution {
public:
    vector<int> minDeletions(string s, vector<vector<int>>& queries) {
        int n = s.size();
        vector<int> v(n);
        for (int i = 1; i < n; i++) v[i] = s[i] == s[i - 1];
        FenwickTree tree(v);
        int t, j, l, r;
        vector<int> ans;
        for (auto &q : queries) {
            t = q[0];
            if (t == 1) {
                int j = q[1];

                int oval = tree.sum(j, j);
                int nval = j == 0 ? 0 : s[j] != s[j - 1];
                int delta = -oval + nval;

                tree.add(j, delta);
                if (j + 1 < n) {
                    oval = tree.sum(j + 1, j + 1);
                    nval = s[j + 1] != s[j];
                    delta = -oval + nval;
                    tree.add(j + 1, delta);
                }

                s[j] ^= 'A' ^ 'B';
            } else {
                int l = q[1] + 1, r = q[2];
                if (l <= r)
                    ans.push_back(tree.sum(l, r));
                else
                    ans.push_back(0);
            }
        }
        return ans;
    }
};