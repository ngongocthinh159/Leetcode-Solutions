struct segtree {
    vector<long long> nodes;
    segtree(int n) {
        nodes.resize(4*n);
    }
    long long merge(long long &l, long long &r) {
        return max(l, r);
    }
    void update(int idx, int s, int e, int pos, long long val) {
        if (s == e) {
            nodes[idx] = max(nodes[idx], val);
            return;
        }
        int m = (s + e)/2;
        if (pos <= m)
            update(2*idx, s, m, pos, val);
        else
            update(2*idx + 1, m + 1, e, pos, val);
        nodes[idx] = merge(nodes[2*idx], nodes[2*idx + 1]);
    }
    long long query(int idx, int s, int e, int l, int r) {
        if (s > r || l > e || s > e || l > r) return 0;
        if (l <= s && e <= r) return nodes[idx];
        int m = (s + e)/2;
        long long lans = query(2*idx, s, m, l, r);
        long long rans = query(2*idx + 1, m + 1, e, l, r);
        return max(lans, rans);
    }
};
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> v = nums;
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        unordered_map<int,int> toIdx;
        for (int i = 0; i < int(v.size()); i++) {
            toIdx[v[i]] = i;
        }
        vector<vector<long long>> dp(n, vector<long long>(2));
        segtree treeup(n);
        segtree treedown(n);
        long long ans = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (i + k < n) {
                treeup.update(1, 0, n - 1, toIdx[nums[i + k]], dp[i + k][1]);
                treedown.update(1, 0, n - 1, toIdx[nums[i + k]], dp[i + k][0]);
            }
            
            // up
            int idx = toIdx[nums[i]];
            long long res1 = treedown.query(1, 0, n - 1, idx + 1, n - 1);
            dp[i][1] = res1 + nums[i];

            // down
            long long res2 = treeup.query(1, 0, n - 1, 0, idx - 1);
            dp[i][0] = res2 + nums[i];

            ans = max(ans, dp[i][0]);
            ans = max(ans, dp[i][1]);
        } 
        return ans;
    }
};