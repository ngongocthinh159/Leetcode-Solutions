class Solution {
public:
    int countTrapezoids(vector<vector<int>>& points) {
        unordered_map<int,int> f;
        for (auto &p : points) f[p[1]]++;
        int p = 0, ans = 0;
        const int MOD = 1e9 + 7;
        for (auto [y, cnt] : f) {
            int cur = 1LL * cnt * (cnt - 1) / 2 % MOD;
            ans += 1LL * cur * p % MOD;
            ans %= MOD;
            p += cur;
            p %= MOD;
        }
        return ans;
    }
};