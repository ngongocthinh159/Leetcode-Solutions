class Solution {
public:
    vector<vector<double>> dp;
    double dfs(int poured, int i, int j) {
        if (i == 1) return poured;
        if (dp[i][j] != -1.0) return dp[i][j];

        double res;
        if (j == 1) {   
            res = max(0.0, dfs(poured, i - 1, j) - 1) / 2.00;    
        } else if (j == i) {
            res = max(0.0, dfs(poured, i - 1, j - 1) - 1) / 2.00;
        } else {
            res = max(0.0, dfs(poured, i - 1, j - 1) - 1) / 2.00 + max(0.0, dfs(poured, i - 1, j) - 1) / 2.00;
        }
        return dp[i][j] = res;
    }
    double champagneTower(int poured, int query_row, int query_glass) {
        dp.assign(query_row + 2, vector<double>(query_glass + 2, -1));
        return min(dfs(poured, query_row + 1, query_glass + 1), 1.0);
    }
};