struct node {
    int pref[5];
    int suf[5];
    int val;
    node() {
        for (int i = 0; i < 5; i++) pref[i] = suf[i] = 0;
        val = 0;
    }
    node(int x) {
        val = x;
    }
};
struct segtree {
    vector<node> nodes;
    int n;
    int k;
    segtree(int _n, int _k, vector<int> &arr) {
        n = _n;
        k = _k;
        nodes.resize(4*n);
        build(1, 0, n - 1, arr);
    }
    node merge(node &l, node &r) {
        node res;
        for (int i = 0; i < k; i++) {
            res.pref[i] += l.pref[i];
            res.pref[(i * l.val) % k] += r.pref[i];
            res.suf[i] += r.suf[i];
            res.suf[(i * r.val) % k] += l.suf[i];
        }
        res.val = l.val * r.val % k;
        return res;
    }
    void build(int idx, int s, int e, vector<int> &arr) {
        if (s == e) {
            int x = arr[s] % k;
            nodes[idx].val = x;
            nodes[idx].pref[x] = 1;
            nodes[idx].suf[x] = 1;
            return;
        }
        int m = (s + e)/2;
        build(2*idx, s, m, arr);
        build(2*idx + 1, m + 1, e, arr);
        nodes[idx] = merge(nodes[2*idx], nodes[2*idx + 1]);
    }
    void update(int idx, int s, int e, int pos, int val) {
        if (s == e) {
            int cval = nodes[idx].val;
            int nval = val % k;
            nodes[idx].pref[cval] = nodes[idx].suf[cval] = 0;
            nodes[idx].val = nval;
            nodes[idx].pref[nval] = nodes[idx].suf[nval] = 1;
            return;
        }
        int m = (s + e)/2;
        if (pos <= m)
            update(2*idx, s, m, pos, val);
        else
            update(2*idx + 1, m + 1, e, pos, val);
        nodes[idx] = merge(nodes[2*idx], nodes[2*idx + 1]);
    }
    node query(int idx, int s, int e, int l, int r) {
        if (s > r || l > e || s > e || l > r) return node(-1);
        if (l <= s && e <= r) return nodes[idx];
        int m = (s + e)/2;
        node lans = query(2*idx, s, m, l, r);
        node rans = query(2*idx + 1, m + 1, e, l, r);
        if (lans.val != -1 && rans.val != -1)
            return merge(lans, rans);
        else if (lans.val == -1) return rans;
        return lans;
    }
};
class Solution {
public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        int n = nums.size();
        int q = queries.size();
        segtree tree(n, k, nums);
        vector<int> ans(q);
        for (int i = 0; i < q; i++) {
            tree.update(1, 0, n - 1, queries[i][0], queries[i][1]);
            ans[i] = tree.query(1, 0, n - 1, queries[i][2], n - 1).pref[queries[i][3]];
        }
        return ans;
    }
};