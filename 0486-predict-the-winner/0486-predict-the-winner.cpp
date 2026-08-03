class Solution {
public:
    bool predictTheWinner(vector<int>& nums) {
        int n = nums.size();
        vector<vector<long long>> dp(n, vector<long long>(n));
        vector<long long> pref(n + 1);
        for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + nums[i];
        for (int i = 0; i < n; i++) dp[i][i] = nums[i];
        for (int len = 2; len <= n; len++)
            for (int l = 0; l + len - 1 < n; l++) {
                int r = l + len - 1;
                long long sum = pref[r + 1] - pref[l];
                dp[l][r] = sum - min(dp[l + 1][r], dp[l][r - 1]);
            }

        return dp[0][n - 1] * 2 >= pref[n];
    }
};