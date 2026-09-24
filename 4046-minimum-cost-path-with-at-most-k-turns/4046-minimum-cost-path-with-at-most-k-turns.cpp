class Solution {
public:
    vector<vector<vector<vector<long long>>>> dp;
    int n, m;
    vector<pair<int,int>> moves = {{1,0},{0,1},{-1,0},{0,-1}};
    long long dfs(int i, int j, int k, int last, vector<vector<int>> &grid) {
        if (i == n - 1 && j == m - 1) return grid[i][j];
        if (dp[i][j][k][last] != -1) return dp[i][j][k][last];
        long long res = 1e15;
        for (int ii = 0; ii < 4; ii++) {
            int cost = ii != last;
            if (k - cost >= 0) {
                int I = moves[ii].first + i;
                int J = moves[ii].second + j;
                if (0 <= I && I < n && 0 <= J && J < m) {
                    res = min(res, grid[i][j] + dfs(I, J, k - cost, ii, grid));
                }
            }
        }
        return dp[i][j][k][last] = res;
    }
    int minCost(vector<vector<int>>& grid, int k) {
        n = grid.size();
        m = grid[0].size();
        dp = vector<vector<vector<vector<long long>>>>(n,
            vector<vector<vector<long long>>>(m,
                vector<vector<long long>>(k + 1,
                    vector<long long>(4, -1))));
        // D,
        long long res = min(dfs(0, 0, k, 0, grid),
            min(dfs(0, 0, k, 1, grid),
            min(dfs(0, 0, k, 2, grid), dfs(0, 0, k, 3, grid))));
        if (res >= 1e15) return -1;
        return res;
    }
};