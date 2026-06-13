class Solution {
public:
    long long maximumSum(vector<int>& nums, int m, int l, int r) {
        int n = nums.size();
        const long long LINF = 1e15 + 5;
        m = min(m, n/l);
        vector<vector<long long>> dp(m + 1, vector<long long>(n + 1, -LINF));
        vector<long long> pref(n + 1);
        for (int i = 1; i <= n; i++) pref[i] = pref[i - 1] + nums[i - 1];
        dp[0][0] = 0;
        for (int i = 0; i <= n; i++) dp[0][i] = 0;
        long long ans = -LINF;

        for (int j = 1; j <= m; j++) {
            deque<pair<int,long long>> q;
            for (int i = 1; i <= n; i++) {
                if (i - l >= 0) {
                    long long cur = dp[j - 1][i - l] - pref[i - l];
                    while (q.size() && cur >= q.front().second) q.pop_front();
                    q.push_front({i - l, cur});
                }

                dp[j][i] = dp[j][i - 1];
                while (q.size() && !((i - r) <= q.back().first && q.back().first <= (i - l))) q.pop_back();
                if (q.size()) {
                    dp[j][i] = max(dp[j][i], pref[i] + q.back().second);
                }
                if (i == n) ans = max(ans, dp[j][i]);
            }
        }
        return ans;
    }
};