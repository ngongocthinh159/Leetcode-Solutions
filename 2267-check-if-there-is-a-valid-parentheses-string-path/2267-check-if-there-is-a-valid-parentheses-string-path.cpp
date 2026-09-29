class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<bitset<100>> dp(m, 0);
        dp[0] = 1;
        for (int i = 0; i < n; i++) {
            vector<bitset<100>> ndp(m);
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '(') {
                    ndp[j] = dp[j] << 1;
                    if (j - 1 >= 0) ndp[j] = ndp[j] | (ndp[j - 1] << 1);
                } else {
                    ndp[j] = dp[j] >> 1;
                    if (j - 1 >= 0) ndp[j] = ndp[j] | (ndp[j - 1] >> 1);
                }
            }
            swap(dp, ndp);
        }
        return dp[m - 1].test(0);
    }
};