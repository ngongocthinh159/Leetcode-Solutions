#define data __data
#define N 100005
int last[N];
struct data {
    int mn, mx, val;
};
struct segtree {
    vector<data> nodes;
    vector<int> lazy;
    int n;
    segtree(int _n) {
        n = _n;
        nodes.resize(4*n);
        lazy.resize(4*n);
    }
    void apply(int idx, int s, int e, int val) {
        nodes[idx].val += val;
        nodes[idx].mn += val;
        nodes[idx].mx += val;
        lazy[idx] += val;
    }
    void push_down(int idx, int s, int e) {
        if (lazy[idx]) {
            int m = (s + e)/2;
            apply(2*idx, s, m, lazy[idx]);
            apply(2*idx + 1, m + 1, e, lazy[idx]);
            lazy[idx] = 0;
        }
    }
    data merge(data& l, data& r) {
        data res;
        res.val = l.val + r.val;
        res.mn = min(l.mn, r.mn);
        res.mx = max(l.mx, r.mx);
        return res;
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
        nodes[idx] = merge(nodes[2*idx], nodes[2*idx + 1]);
    }
    int query(int idx, int s, int e, int l, int r) {
        if (!(nodes[idx].mn <= 0 && 0 <= nodes[idx].mx)) return -1;
        if (s > r || l > e || s > e || l > r) return -1;
        if (s == e) return s;
        push_down(idx, s, e);
        int m = (s + e)/2;
        int lans = query(2*idx, s, m, l, r);
        if (lans != -1) return lans;
        return query(2*idx + 1, m + 1, e, l, r);
    }
};
class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        for (auto x : nums) last[x] = -1;
        segtree tree(n);
        for (int i = 0; i < n; i++) {
            int sidx = last[nums[i]] + 1;
            int delta = (nums[i] & 1) ? -1 : 1;

            tree.update(1, 0, n - 1, sidx, i, delta);
            int idx = tree.query(1, 0, n - 1, 0, i);
            if (idx != -1) 
                ans = max(ans, i - idx + 1);

            last[nums[i]] = i;
        }
        return ans;
    }
};