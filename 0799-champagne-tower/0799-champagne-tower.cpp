class Solution {
public:
    vector<vector<double>> dp;
    double champagneTower(int poured, int query_row, int query_glass) {
        dp.assign(query_row + 2, vector<double>(query_row + 2, 0));
        dp[0][0] = poured;
        for (int i = 0; i < query_row; i++)
            for (int j = 0; j <= i; j++) if (dp[i][j] > 1.00) {
                dp[i][j] -= 1.00;
                dp[i + 1][j] += dp[i][j] / 2.00;
                dp[i + 1][j + 1] += dp[i][j] / 2.00;
            }
        return min(dp[query_row][query_glass], 1.00);
    }
};