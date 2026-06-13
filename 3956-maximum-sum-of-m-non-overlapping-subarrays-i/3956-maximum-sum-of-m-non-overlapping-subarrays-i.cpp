class Solution {
public:
    long long maximumSum(vector<int>& nums, int m, int l, int r) {
        int n = nums.size();
        const long long LINF = 1e15 + 5;
        vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, -LINF));
        vector<long long> pref(n + 1);
        for (int i = 1; i <= n; i++) pref[i] = pref[i - 1] + nums[i - 1];
        dp[0][0] = 0;
        for (int i = 0; i <= n; i++) dp[i][0] = 0;
        long long ans = -LINF;

        for (int j = 1; j <= m; j++) {
            deque<pair<int,long long>> q;
            for (int i = 1; i <= n; i++) {
                if (i - l >= 0) {
                    long long cur = dp[i - l][j - 1] - pref[i - l];
                    while (q.size() && cur >= q.front().second) q.pop_front();
                    q.push_front({i - l, cur});
                }

                dp[i][j] = max(dp[i][j], dp[i - 1][j]);
                while (q.size() && !((i - r) <= q.back().first && q.back().first <= (i - l))) q.pop_back();
                if (q.size()) {
                    dp[i][j] = max(dp[i][j], pref[i] + q.back().second);
                }
                if (i == n) ans = max(ans, dp[i][j]);
            }
        }
        // for (int i = 1; i <= n; i++) {
        //     {
        //         for (int j = 0; j <= m; j++) {
        //             auto &q = col[j];
        //             if (i - l >= 0) {
        //                 long long cur = dp[i - l][j] - pref[i - l];
        //                 while (q.size() && cur >= q.front().second) q.pop_front();
        //                 q.push_front({i - l, cur});
        //             }
        //         }
        //     }

        //     dp[i][0] = 0;
        //     for (int j = 1; j <= m; j++) {
        //         dp[i][j] = max(dp[i][j], dp[i - 1][j]);
        //         {
        //             auto &q = col[j - 1];
        //             while (q.size() && !((i - r) <= q.back().first && q.back().first <= (i - l))) {
        //                 q.pop_back();
        //             }
        //             if (q.size()) dp[i][j] = max(dp[i][j], pref[i] + q.back().second);
        //         }
        //         // for (int k = max(i - r, 0); k <= i - l; k++) {
        //         //     dp[i][j] = max(dp[i][j], dp[k][j - 1] + pref[i] - pref[k]);
        //         // }
        //         // dp[i - l][j - 1] -> dp[i - r][j - 1]
        //     }

        // }
        return ans;
    }
};