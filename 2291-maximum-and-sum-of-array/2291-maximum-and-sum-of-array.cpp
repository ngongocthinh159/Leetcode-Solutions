#define N 18
int dp[N][1 << N];
class Solution {
public:
    int maximumANDSum(vector<int>& nums, int m) {
        int n = nums.size();
        vector<vector<int>> dp(m + 1, vector<int>(1 << n, -1));
        int fmask = (1 << n) - 1;
        dp[0][fmask] = 0;
        for (int i = 0; i < m; i++)
            for (int mask = 0; mask <= fmask; mask++) if (dp[i][mask] != -1) {
                int remain = __builtin_popcount(mask);
                int can = remain == 0 || (remain - 1) <= (m - i - 1) * 2;
                int can2 = remain == 0 || remain <= (m - i - 1) * 2;
                int ni = i + 1, nmask;
                if (can) {
                    for (int j = 0; j < n; j++) if ((mask >> j) & 1) {
                        nmask = mask ^ (1 << j);
                        dp[ni][nmask] = max(dp[ni][nmask], dp[i][mask] + (nums[j] & (i + 1)));
                    }
                }
                if (can2) dp[ni][mask] = max(dp[ni][mask], dp[i][mask]);
                for (int j = 0; j < n; j++) if ((mask >> j) & 1)
                    for (int k = 0; k < n; k++) if (k != j && ((mask >> k) & 1)) {
                        nmask = mask ^ (1 << j) ^ (1 << k);
                        int cost = (nums[j] & (i + 1)) + (nums[k] & (i + 1));
                        dp[ni][nmask] = max(dp[ni][nmask], dp[i][mask] + cost);
                    }
            }

        return dp[m][0];
    }
};