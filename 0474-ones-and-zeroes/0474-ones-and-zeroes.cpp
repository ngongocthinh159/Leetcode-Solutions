class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int N = strs.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int i = 0; i < N; i++) {
            vector<vector<int>> ndp = dp;
            int Z = 0, O = 0;
            for (auto c : strs[i]) {
                if (c == '0') Z++;
                else O++;
            }
            for (int z = 0; z <= m; z++)
                for (int o = 0; o <= n; o++) if (z >= Z && o >= O)
                    ndp[z][o] = max(ndp[z][o], 1 + dp[z - Z][o - O]);
            swap(dp, ndp);
        }
        int ans = 0;
        for (int z = 0; z <= m; z++)
            for (int o = 0; o <= n; o++) ans = max(ans, dp[z][o]);
        return ans;
    }
};