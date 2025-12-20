#define N 1005
long long dp[N][N/2][3]; 
class Solution {
public:
    long long maximumProfit(vector<int>& prices, int k) {
        int n = prices.size();
        long long ans = 0;
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= k; j++)
                for (int t = 0; t < 3; t++) dp[i][j][t] = INT_MIN;
        
        dp[0][0][0] = 0;
        dp[0][0][1] = -prices[0];
        dp[0][0][2] = prices[0];
        for (int i = 1; i < n; i++) {
            long long p = prices[i];
            dp[i][0][0] = 0;
            dp[i][0][1] = max(dp[i - 1][0][1], -p);
            dp[i][0][2] = max(dp[i - 1][0][2], p);
            for (int j = 1; j <= k; j++) {
                dp[i][j][0] = max(dp[i - 1][j][0], 
                            max(dp[i - 1][j - 1][1] + p, dp[i - 1][j - 1][2] - p));
                dp[i][j][1] = max(dp[i - 1][j][0] - p, dp[i - 1][j][1]);
                dp[i][j][2] = max(dp[i - 1][j][0] + p, dp[i - 1][j][2]);
                if (i == n - 1) ans = max(ans, dp[i][j][0]);
            }
        }
        return ans;
    }
};