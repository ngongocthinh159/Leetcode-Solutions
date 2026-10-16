struct Node {
    int sum;
    int ssum;
};
struct Segtree {
    int n;
    vector<Node> nodes;
    vector<int> lazy;
    const int MOD = 1e9 + 7;
    Segtree(int _n) {
        n = _n;
        nodes.resize(4*n);
        lazy.resize(4*n);
    }
    Node merge(const Node &l, const Node& r) {
        Node res;
        res.sum = (l.sum + r.sum) % MOD;
        res.ssum = (l.ssum + r.ssum) % MOD;
        return res;
    }
    void push_down(int idx, int s, int e) {
        if (lazy[idx]) {
            int m = (s + e)/2;
            apply(2*idx, s, m, lazy[idx]);
            apply(2*idx + 1, m + 1, e, lazy[idx]);
            lazy[idx] = 0;
        }
    }
    void apply(int idx, int s, int e, int delta) {
        nodes[idx].ssum += 2ll * delta * nodes[idx].sum % MOD + 1ll * (e - s + 1) * delta % MOD * delta % MOD;
        nodes[idx].ssum %= MOD;
        nodes[idx].sum += 1ll * delta * (e - s + 1) % MOD;
        nodes[idx].sum %= MOD;

        lazy[idx] += delta;
        lazy[idx] %= MOD;
    }
    void update(int idx, int s, int e, int l, int r, int delta) {
        if (s > r || l > e || s > e || l > r) return;
        if (l <= s && e <= r) {
            apply(idx, s, e, delta);
            return;
        }
        push_down(idx, s, e);
        int m = (s + e)/2;
        update(2*idx, s, m, l, r, delta);
        update(2*idx + 1, m + 1, e, l, r, delta);
        nodes[idx] = merge(nodes[2*idx], nodes[2*idx + 1]);
    }
    Node query(int idx, int s, int e, int l, int r) {
        if (s > r || l > e || s > e || l > r) return Node{0, 0};
        if (l <= s && e <= r) return nodes[idx];
        push_down(idx, s, e);
        int m = (s + e)/2;
        return merge(query(2*idx, s, m, l, r), query(2*idx + 1, m + 1, e, l, r));
    }
};
class Solution {
public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        Segtree tree(n + 1);
        unordered_map<int,int> last;
        const int MOD = 1e9 + 7;
        for (int i = 0; i < n; i++) {
            if (last.count(nums[i])) {
                tree.update(1, 0, n, last[nums[i]] + 1, n, -1);
            }
            tree.update(1, 0, n, i + 1, n, 1);

            int u = tree.query(1, 0, n, i + 1, i + 1).sum;
            Node v = tree.query(1, 0, n, 0, i);
            int tmp = 1ll * (i + 1) * u % MOD * u % MOD;
            tmp = ((tmp - 2ll * u * v.sum % MOD) % MOD + MOD) % MOD;
            tmp = (tmp + v.ssum) % MOD;

            ans = (ans + tmp) % MOD;

            last[nums[i]] = i;
        }
        return ans;
    }
};