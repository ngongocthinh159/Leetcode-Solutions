class Solution {
public:
    long long maxTaxiEarnings(int m, vector<vector<int>>& rides) {
        int n = rides.size();
        sort(rides.begin(), rides.end());
        vector<long long> dp(n + 1);
        dp[n] = 0;
        for (int i = n - 1; i >= 0; i--) {
            dp[i] = dp[i + 1];
            vector<int> key = {rides[i][1], INT_MIN};
            auto it = lower_bound(rides.begin() + i + 1, rides.end(), key);
            int idx = it - rides.begin();
            dp[i] = max(dp[i], rides[i][1] - rides[i][0] + rides[i][2] + dp[idx]);
        }
        return dp[0];
    }
};