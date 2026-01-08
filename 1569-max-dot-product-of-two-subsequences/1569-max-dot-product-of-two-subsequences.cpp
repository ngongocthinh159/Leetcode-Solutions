#define ll long long
class Solution {
public:
    const int IINF = 1e9;
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, -IINF));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                dp[i][j] = max(dp[i][j], nums1[i - 1] * nums2[j - 1] + max(0LL, dp[i - 1][j - 1]));
                dp[i][j] = max(dp[i][j], dp[i - 1][j]);
                dp[i][j] = max(dp[i][j], dp[i][j - 1]);
            }
        return dp[n][m];
    }
};