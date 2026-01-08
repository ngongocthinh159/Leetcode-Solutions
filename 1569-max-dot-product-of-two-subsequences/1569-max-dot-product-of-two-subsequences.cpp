#define ll long long
class Solution {
public:
    const int IINF = 1e9;
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        vector<vector<vector<ll>>> dp(n + 1, 
            vector<vector<ll>>(m + 1, 
                vector<ll>(2, -IINF)));
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= m; j++) dp[i][j][0] = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                dp[i][j][1] = max(dp[i][j][1], nums1[i - 1] * nums2[j - 1] + max(dp[i - 1][j - 1][0], dp[i - 1][j - 1][1]));
                dp[i][j][1] = max(dp[i][j][1], dp[i - 1][j][1]);
                dp[i][j][1] = max(dp[i][j][1], dp[i][j - 1][1]);
            }
        return dp[n][m][1];
    }
};