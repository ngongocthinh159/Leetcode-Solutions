struct segtree {
    vector<int> nodes;
    segtree(int n) {
        nodes.resize(4*n);
    }
    void update(int idx, int s, int e, int pos, int val) {
        if (s == e) {
            nodes[idx] = max(nodes[idx], val);
            return;
        }
        int m = (s + e)/2;
        if (pos <= m)
            update(2*idx, s, m, pos, val);
        else 
            update(2*idx + 1, m + 1, e, pos, val);
        nodes[idx] = max(nodes[2*idx], nodes[2*idx + 1]);
    }
    int query(int idx, int s, int e, int l, int r) {
        if (s > r || l > e || s > e || l > r) return 0;
        if (l <= s && e <= r) return nodes[idx];
        int m = (s + e)/2;
        int lans = query(2*idx, s, m, l, r);
        int rans = query(2*idx + 1, m + 1, e, l, r);
        return max(lans, rans);
    }
};
class Solution {
public:
    int maxFixedPoints(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        vector<pair<int,int>> v;
        for (int i = 0; i < n; i++) v.push_back({nums[i], i});
        sort(v.begin(), v.end());

        vector<int> tmp;
        for (int i = 0; i < n; i++) tmp.push_back(nums[i] - i);
        sort(tmp.begin(), tmp.end());
        tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
        unordered_map<int,int> toIdx;
        for (int i = 0; i < int(tmp.size()); i++) toIdx[tmp[i]] = i;

        segtree tree(n);
        vector<int> dp(n);
        for (int i = n - 1; i >= 0;) {
            int cur = v[i].first;
            int end = i, st = i;
            while (i >= 0 && cur == v[i].first) {
                int idx = v[i].second;
                int val = nums[idx] - idx;

                dp[idx] = 1 + tree.query(1, 0, n - 1, 0, toIdx[val]);

                if (idx >= nums[idx]) ans = max(ans, dp[idx]);

                st = i;
                i--;
            }
            for (int j = st; j <= end; j++) {
                int idx = v[j].second;
                int val = nums[idx] - idx;
                tree.update(1, 0, n - 1, toIdx[val], dp[idx]);
            }
        }
       
        return ans;
    }
};