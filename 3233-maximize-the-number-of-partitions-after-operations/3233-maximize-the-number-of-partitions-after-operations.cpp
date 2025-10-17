struct segtree {
    vector<int> node;
    int n;
    segtree(string &str) {
        n = str.size();
        node.resize(4*n);
        build(1, 0, n - 1, str);
    }
    void build(int idx, int s, int e, string &str) {
        if (s == e) {
            node[idx] = (1 << (str[s] - 'a'));
            return;
        }
        int m = (s + e)/2;
        build(2*idx, s, m, str);
        build(2*idx + 1, m + 1, e, str);
        node[idx] = merge(node[2*idx], node[2*idx + 1]);
    }
    int merge(int &l, int &r) {
        return l | r;
    }
    void update(int idx, int s, int e, int pos, char c) {
        if (s == e) {
            node[idx] = (1 << (c - 'a'));
            return;
        }
        int m = (s + e)/2;
        if (pos <= m)
            update(2*idx, s, m, pos, c);
        else
            update(2*idx + 1, m + 1, e, pos, c);
        node[idx] = merge(node[2*idx], node[2*idx + 1]);
    }
    int query(int idx, int s, int e, int l, int r) {
        if (s > r || l > e || s > e || l > r) return 0;
        if (l <= s && e <= r) return node[idx];
        int m = (s + e)/2;
        int lans = query(2*idx, s, m, l, r);
        int rans = query(2*idx + 1, m + 1, e, l, r);
        return merge(lans, rans);
    }
};
class Solution {
public:
    int n;
    int findEnd(int idx, segtree &tree, int k) {
        int l = idx - 1, r = n;
        while (r - l > 1) {
            int m = l + (r - l)/2;
            if (__builtin_popcount(tree.query(1, 0, n - 1, idx, m)) <= k)
                l = m;
            else
                r = m;
        }
        return l;
    }
    int maxPartitionsAfterOperations(string s, int k) {
        n = s.size();
        segtree tree(s);
        vector<int> iToSegId(n);
        vector<pair<int,int>> seg;
        for (int i = 0; i < n; ) {
            int st = i, e = i;
            int id = seg.size();
            int mask = 0;
            while (i < n && __builtin_popcount(mask | (1 << (s[i] - 'a'))) <= k) {
                mask |= (1 << (s[i] - 'a'));
                e = i;
                i++;
            }
            for (int j = st; j <= e; j++) iToSegId[j] = id;
            seg.push_back({st, e});
        }
        int ans = seg.size();
        vector<int> surf(n + 2);
        for (int i = n - 1; i >= 0; i--) {
            int e = findEnd(i, tree, k);
            surf[i + 1] = 1 + surf[e + 2];
        }
        for (int i = 0; i < n; i++) {
            int id = iToSegId[i];
            char orgC = s[i];
            for (int c = 0; c < 26; c++) if (c + 'a' != orgC) {
                tree.update(1, 0, n - 1, i, c + 'a');
                int e1 = findEnd(seg[id].first, tree, k);
                if (e1 >= i) {
                    ans = max(ans, id + 1 + surf[e1 + 2]);
                } else {
                    int e2 = findEnd(i, tree, k);
                    ans = max(ans, id + 1 + 1 + surf[e2 + 2]);
                }
            }
            tree.update(1, 0, n - 1, i, orgC);
        }
        return ans;
    }
};