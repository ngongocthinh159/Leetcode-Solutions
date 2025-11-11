struct Data {
    int mn, mx;
};
struct segtree {
    vector<Data> node;
    vector<int> lazy;
    int n;
    segtree(int _n) {
        n = _n;
        node.resize(4*n);
        lazy.resize(4*n);
    }
    void apply(int idx, int s, int e, int delta) {
        node[idx].mn += delta;
        node[idx].mx += delta;
        lazy[idx] += delta;
    }
    void push_down(int idx, int s, int e) {
        if (lazy[idx]) {
            int m = (s + e) / 2;
            apply(2*idx, s, m, lazy[idx]);
            apply(2*idx + 1, m + 1, e, lazy[idx]);
            lazy[idx] = 0;
        }
    }
    Data merge(Data &l, Data &r) {
        Data res;
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
        node[idx] = merge(node[2*idx], node[2*idx + 1]);
    }
    int left_most_zero(int idx, int s, int e) {
        if (!(node[idx].mn <= 0 && 0 <= node[idx].mx)) return -1;
        if (s == e) return s;
        push_down(idx, s, e);
        int m = (s + e)/2;
        int lans = left_most_zero(2*idx, s, m);
        if (lans != -1) return lans;
        return left_most_zero(2*idx +1, m + 1, e);
    }
};
class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        unordered_map<int,int> last;
        vector<int> toSign = {1, -1};
        segtree tree(n);
        for (int i = 0; i < n; i++) {
            int sign = toSign[nums[i] & 1];
            if (last.count(nums[i]))
                tree.update(1, 0, n - 1, 0, last[nums[i]], -sign);
            last[nums[i]] = i;
            tree.update(1, 0, n - 1, 0, last[nums[i]], sign);
            int idx = tree.left_most_zero(1, 0, n - 1);
            if (idx != -1 && idx <= i)
                ans = max(ans, i - idx + 1);
        }
        return ans;
    }
};  