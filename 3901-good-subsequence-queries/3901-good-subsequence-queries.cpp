#define data __data
struct segtree {
    vector<int> nodes;
    segtree(int n) {
        nodes.resize(4*n);
    }
    int merge(int&l, int&r) {
        int res;
        if (l == -1) res = r;
        else if (r == -1) res = l;
        else res = gcd(l, r);
        return res;
    }
    void update(int idx, int s, int e, int pos, int val) {
        if (s == e) {
            nodes[idx] = val;
            return;
        }
        int m = (s + e)/2;
        if (pos <= m) 
            update(2*idx, s, m, pos, val);
        else 
            update(2*idx + 1, m + 1, e, pos, val);
        nodes[idx] = merge(nodes[2*idx], nodes[2*idx + 1]);
    }
    int query(int idx, int s, int e, int l, int r) {
        if (s > r || l > e || s > e || l > r) return -1;
        if (l <= s && e <= r) return nodes[idx];
        int m = (s + e)/2;
        int lans = query(2*idx, s, m, l, r);
        int rans = query(2*idx + 1, m + 1, e, l, r);
        if (lans == -1) return rans;
        if (rans == -1) return lans;
        return gcd(lans, rans);
    }
};
class Solution {
public:
    int countGoodSubseq(vector<int>& nums, int p, vector<vector<int>>& queries) {
        int n = nums.size();
        segtree tree(n);
        int cnt = 0, ans = 0;
        for (int i = 0; i < n; i++) {
            tree.update(1, 0, n - 1, i, nums[i] % p == 0 ? nums[i] : -1);
            if (nums[i] % p == 0) cnt++;
        }
        for (int i = 0; i < int(queries.size()); i++) {
            auto &q = queries[i];
            int idx, newVal, oldVal;
            idx = q[0];
            newVal = q[1];
            oldVal = nums[idx];

            if (oldVal % p == 0) cnt--;
            if (newVal % p == 0) cnt++;
            tree.update(1, 0, n - 1, idx, newVal % p == 0 ? newVal : -1);

            if (tree.query(1, 0, n - 1, 0, n - 1) == p) {
                if (cnt != n) ans++;
                else {
                    if (cnt > 32) {
                        ans++;
                    } else {
                        for (int i = 0; i < n; i++) {
                            int l = tree.query(1, 0, n - 1, 0, i - 1);
                            int r = tree.query(1, 0, n - 1, i + 1, n - 1);
                            if (l == -1) {
                                if (r == p) {
                                    ans++;
                                    break;
                                }
                            } else if (r == -1) {
                                if (l == p) {
                                    ans++;
                                    break;
                                }
                            } else {
                                if (gcd(l, r) == p) {
                                    ans++;
                                    break;
                                }
                            }
                        }
                    }
                }
            }

            nums[idx] = newVal;
        }
        return ans;
    }
};