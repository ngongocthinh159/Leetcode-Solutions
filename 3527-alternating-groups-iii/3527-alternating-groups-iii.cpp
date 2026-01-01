struct segtree {
    vector<int> node;
    vector<int> lazy;
    int n;
    segtree(vector<int> &arr) {
        n = arr.size();
        node.resize(4*n);
        lazy.resize(4*n);
        build(1, 0, n - 1, arr);
    }
    void build(int idx, int s, int e, vector<int> &arr) {
        if (s == e) {
            node[idx] = arr[s];
            return;
        }
        int m = (s + e)/2;
        build(2*idx, s, m, arr);
        build(2*idx + 1, m + 1, e, arr);
        node[idx] = merge(node[2*idx], node[2*idx + 1]);
    }
    void apply(int idx, int s, int e, int val) {
        node[idx] += (e - s + 1) * val;
        lazy[idx] += val;
    }
    void push_down(int idx, int s, int e) {
        if (lazy[idx] != 0) {
            int m = (s + e)/2;
            apply(2*idx, s, m, lazy[idx]);
            apply(2*idx + 1, m + 1, e, lazy[idx]);
            lazy[idx] = 0;
        }
    }
    int merge(int &l, int &r) {
        return l + r;
    }
    void update(int idx, int s, int e, int l, int r, int val) {
        if (s > r || l > e || s > e || l > r) return;
        if (l <= s && e <= r) {
            apply(idx, s, e, val);
            return;
        }
        push_down(idx, s, e);
        int m = (s + e)/2;
        update(2*idx, s, m, l, r, val);
        update(2*idx + 1, m + 1, e, l, r, val);
        node[idx] = merge(node[2*idx], node[2*idx + 1]);
    }
    int query(int idx, int s, int e, int l, int r) {
        if (s > r || l > e || s > e || l > r) return 0;
        if (l <= s && e <= r) return node[idx];
        push_down(idx, s, e);
        int m = (s + e)/2;
        auto lans = query(2*idx, s, m, l, r);
        auto rans = query(2*idx + 1, m + 1, e, l, r);
        return merge(lans, rans);
    }
    void print() {
        for (int i = 0; i < n; i++) {
            cout << query(1, 0, n - 1, i, i) << ' ';
        }
        cout << '\n';
        cout << '\n';
    }
};

class Solution {
public:
    int find_furthest(int idx, segtree& dptree, int n) {
        int l = idx, r = n;
        while (r - l > 1) {
            int m = l + (r - l)/2;
            if (m - dptree.query(1, 0, n - 1, m, m) + 1 <= idx)
                l = m;
            else
                r = m;
        }
        return l;
    }
    vector<int> numberOfAlternatingGroups(vector<int>& colors, vector<vector<int>>& queries) {
        int n = colors.size();
        int N = n + 1;
        vector<int> dp(n);
        vector<int> lenf(N);
        for (int i = 0; i < n; i++)
            dp[i] = 1 + (i == 0 ? 0 : (colors[i] != colors[i - 1] ? dp[i - 1] : 0)), lenf[dp[i]]++;
        segtree tree(lenf);
        segtree dptree(dp);
        // dptree.print();
        // tree.print();
        int m = queries.size();
        vector<int> ans;
        ans.reserve(queries.size());
        int t, sz, idx, c;
        for (int i = 0; i < m; i++) {
            t = queries[i][0];
            if (t == 1) {
                sz = queries[i][1];
                int res = tree.query(1, 0, N - 1, sz, N - 1);
                if (colors[n - 1] != colors[0]) {
                    int fidx = find_furthest(0, dptree, n);
                    // cout << fidx << '\n';
                    int eidx = min(sz - 2, fidx);
                    if (eidx >= 0) {
                        int s1 = n - (sz - 1);
                        int s2 = n - (sz - eidx - 1);
                        // cout << s1 << ' ' << s2 << '\n';
                        int lastdpidx = n - dptree.query(1, 0, n - 1, n - 1, n - 1);
                        if (lastdpidx <= s2) {
                            // cout << s1 << ' ' << lastdpidx << '\n';
                            int st = max(s1, lastdpidx);
                            int end = s2;
                            res += (end - st + 1);
                        }
                    }
                }
                ans.push_back(res);

            } else {
                idx = queries[i][1], c = queries[i][2];
                if (colors[idx] == c) continue;

                int orgdp = dptree.query(1, 0, n - 1, idx, idx);
                int newdp;
                if (idx - 1 >= 0) {
                    if (colors[idx] == colors[idx - 1])
                        newdp = dptree.query(1, 0, n - 1, idx - 1, idx - 1) + 1;    
                    else
                        newdp = 1;
                    dptree.update(1, 0, n - 1, idx, idx, newdp - orgdp);
                } else
                    newdp = orgdp;
                tree.update(1, 0, N - 1, orgdp, orgdp, -1);
                tree.update(1, 0, N - 1, newdp, newdp, 1);

                if (idx + 1 < n) {
                    int fidx = find_furthest(idx + 1, dptree, n);
                    // cout << fidx << '\n';
                    int len = fidx - (idx + 1) + 1;
                    int delta = colors[idx] == colors[idx + 1] ? newdp : -orgdp;
                    // cout << delta << '\n';
                    // dptree.print();
                    int st = dptree.query(1, 0, n - 1, idx + 1, idx + 1);
                    int end = st + len - 1;
                    int nst = st + delta;
                    int nend = nst + len - 1;
                    // cout << st << ' ' << end << ' ' << nst << ' ' << nend << "\n";

                    dptree.update(1, 0, n - 1, idx + 1, fidx, delta);

                    if (st != nst) {
                        tree.update(1, 0, N - 1, st, end, -1);
                        tree.update(1, 0, N - 1, nst, nend, 1);
                    }
                }

                colors[idx] = c;

                // dptree.print();
                // tree.print();
            }
        }
        return ans;
    }
};