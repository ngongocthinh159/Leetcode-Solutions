class Solution {
public:
    long long maxTotal(vector<int>& nums, string s) {
        int n = nums.size();
        const long long LINF = 1e18 + 5;
        vector<vector<long long>> dp(n + 1, vector<long long>(2));
        for (int i = 1; i <= n; i++) {
            if (s[i - 1] == '0') {
                dp[i][1] = -LINF;
                dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
            } else {
                if (i != 1) {
                    dp[i][0] = dp[i - 1][0] + nums[i - 2];
                } else dp[i][0] = -LINF;
                dp[i][1] = max(dp[i - 1][0], dp[i - 1][1]) + nums[i - 1];
            }
        }
        return max(dp[n][0], dp[n][1]);
    }
};