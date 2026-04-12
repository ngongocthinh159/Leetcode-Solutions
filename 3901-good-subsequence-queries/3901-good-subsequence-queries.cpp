#define data __data
struct data {
    int val, g, aIdx;
};
struct segtree {
    vector<data> nodes;
    segtree(int n) {
        nodes.resize(4*n);
    }
    data merge(data&l, data&r) {
        data res;
        res.g = gcd(l.g, r.g);
        return res;
    }
    void update(int idx, int s, int e, int pos, int val, int aIdx) {
        if (s == e) {
            nodes[idx] = data{val,val, aIdx};
            return;
        }
        int m = (s + e)/2;
        if (pos <= m) update(2*idx, s, m, pos, val, aIdx);
        else update(2*idx + 1, m + 1, e, pos, val, aIdx);
        nodes[idx] = merge(nodes[2*idx], nodes[2*idx + 1]);
    }
    int queryGcd(int idx, int s, int e, int l, int r) {
        if (s > r || l > e || s > e || l > r) return -1;
        if (l <= s && e <= r) {
            return nodes[idx].g;
        }
        int m = (s + e)/2;
        int lans = queryGcd(2*idx, s, m, l, r);
        int rans = queryGcd(2*idx + 1, m + 1, e, l, r);
        if (lans == -1) return rans;
        if (rans == -1) return lans;
        return gcd(lans, rans);
    }
    int queryVal(int idx, int s, int e, int pos) {
        if (s == e) return nodes[idx].val;
        int m = (s + e)/2;
        if (pos <= m) return queryVal(2*idx, s, m, pos);
        return queryVal(2*idx + 1, m + 1, e, pos);
    }
    int queryAIdx(int idx, int s, int e, int pos) {
        if (s == e) return nodes[idx].aIdx;
        int m = (s + e)/2;
        if (pos <= m) return queryAIdx(2*idx, s, m, pos);
        return queryAIdx(2*idx + 1, m + 1, e, pos);
    }
};
class Solution {
public:
    int countGoodSubseq(vector<int>& nums, int p, vector<vector<int>>& queries) {
        int n = nums.size();
        segtree tree(n);
        int top = 0, ans = 0;
        unordered_map<int,int> toTreeIdx;
        for (int i = 0; i < n; i++) if (nums[i] % p == 0) {
            tree.update(1, 0, n - 1, top, nums[i], i);
            toTreeIdx[i] = top++;
        }
        // cout << top << '\n';
        for (int i = 0; i < int(queries.size()); i++) {
            auto &q = queries[i];
            int idx, newVal, oldVal;
            idx = q[0];
            newVal = q[1];
            oldVal = nums[idx];

            // cout << i << '\n';

            if (oldVal % p == 0) {
                int treeIdx = toTreeIdx[idx];
                if (treeIdx == top - 1) {
                    toTreeIdx.erase(idx);
                } else {
                    int aIdx = tree.queryAIdx(1, 0, n - 1, top - 1);
                    // cout << aIdx << '\n';
                    toTreeIdx[aIdx] = treeIdx;
                    tree.update(1, 0, n - 1, treeIdx, nums[aIdx], aIdx);
                }
                top--;
            }

            // cout << "here\n";
            if (newVal % p == 0) {
                tree.update(1, 0, n - 1, top, newVal, idx);
                toTreeIdx[idx] = top;
                top++;
            }
            // cout << "here2\n";

            if (tree.queryGcd(1, 0, n - 1, 0, top - 1) == p) {
                if (top != n) ans++;
                else {
                    if (top > 32) {
                        ans++;
                    } else {
                        for (int i = 0; i < top; i++) {
                            int l = tree.queryGcd(1, 0, n - 1, 0, i - 1);
                            int r = tree.queryGcd(1, 0, n - 1, i + 1, top - 1);
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