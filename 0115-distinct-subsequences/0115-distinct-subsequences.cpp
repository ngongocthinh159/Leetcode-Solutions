class Solution {
public:
    const int MOD = 1e9 + 7;
    int numDistinct(string s, string t) {
        int n = s.size(), m = t.size();
        if (n < m) return 0;
        vector<long long> dp(m + 1);
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            vector<long long> ndp = dp;
            for (int j = 0; j <= m; j++) {
                ndp[j] = dp[j];
                if (j > 0 && s[i - 1] == t[j - 1]) {
                    ndp[j] += dp[j - 1];
                    if (ndp[j] >= MOD) ndp[j] -= MOD;
                }
            }

            swap(dp, ndp);
        }
        return dp[m];
    }
};