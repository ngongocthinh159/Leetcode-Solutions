class Solution {
public:
    const int MOD = 1e9 + 7;
    void add(int &x, int y) {
        x += y;
        if (x >= MOD) x-= MOD;
    }
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(k));
        dp[0][grid[0][0] % k] = 1;
        for (int i = 0; i < n; i++) {
            vector<vector<int>> ndp(m, vector<int>(k));
            for (int j = 0; j < m; j++) {
                for (int p = 0; p < k; p++) {
                    if (i + 1 < n) 
                        add(ndp[j][(p + grid[i + 1][j]) % k], dp[j][p]);
                    if (j + 1 < m)
                        add(dp[j + 1][(p + grid[i][j + 1]) % k], dp[j][p]);
                }
            }
            if (i == n - 1)
                return dp[m - 1][0];
            swap(dp, ndp);
        }
        return -1;
    }
};