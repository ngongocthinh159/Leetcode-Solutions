class Solution {
public:
    const long long LINF = 1e15 + 5;
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size(), m = nums2.size();
        vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, 0));
        for (int cnt = 0; cnt < k; cnt++) {
            vector<vector<long long>> ndp(n + 1, vector<long long>(m + 1, -LINF));
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= m; j++) {
                    long long x = nums1[i - 1], y = nums2[j - 1];
                    ndp[i][j] = max(ndp[i][j], ndp[i - 1][j]);
                    ndp[i][j] = max(ndp[i][j], ndp[i][j - 1]);
                    ndp[i][j] = max(ndp[i][j], dp[i - 1][j - 1] + x * y);
                }
            swap(dp, ndp);
        }
        return dp[n][m];
    }
};