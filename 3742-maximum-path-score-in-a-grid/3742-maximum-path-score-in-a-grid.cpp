class Solution {
public:
    int maxPathScore(vector<vector<int>>& grid, int k) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<vector<int>>> dp(n, 
            vector<vector<int>>(m,
                vector<int>(k + 1, -1)));
        dp[0][0][grid[0][0] >= 1] = grid[0][0];
        int ans = -1;
        vector<vector<int>> moves = {{1,0},{0,1}};
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                for (int cost = 0; cost <= k; cost++) if (dp[i][j][cost] != -1) {
                    for (auto &move : moves) {
                        int I = i + move[0];
                        int J = j + move[1];
                        if (0 <= I && I < n && 0 <= J && J < m) {
                            int nCost = cost + (grid[I][J] >= 1);
                            if (nCost <= k)
                                dp[I][J][nCost] = max(dp[I][J][nCost], dp[i][j][cost] + grid[I][J]);
                        }
                    }
                    if (i == n - 1 && j == m - 1) ans = max(ans, dp[i][j][cost]);
                }
        return ans;
    }
};