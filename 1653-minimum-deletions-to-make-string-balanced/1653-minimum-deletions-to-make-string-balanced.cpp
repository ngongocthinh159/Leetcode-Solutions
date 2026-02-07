class Solution {
public:
    const int IINF = 1e9 + 5;
    int minimumDeletions(string s) {
        int n = s.size();
        vector<vector<int>> dp(n + 1, vector<int>(2));
        dp[0][0] = 0, dp[0][1] = IINF;
        for (int i = 1; i <= n; i++) {
            char c = s[i - 1] - 'a';
            dp[i][0] = dp[i - 1][0] + (c != 0);
            if (c == 0) dp[i][1] = dp[i - 1][1] + 1;
            else dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]);
        }
        return min(dp[n][0], dp[n][1]);
    }
};