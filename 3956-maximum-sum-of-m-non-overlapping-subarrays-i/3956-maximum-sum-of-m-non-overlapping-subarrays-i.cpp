class Solution {
public:
    long long maximumSum(vector<int>& nums, int m, int l, int r) {
        int n = nums.size();
        const long long LINF = 1e15 + 5;
        m = min(m, n/l);
        vector<long long> pref(n + 1);
        for (int i = 1; i <= n; i++) pref[i] = pref[i - 1] + nums[i - 1];
        vector<long long> dp(n + 1, 0);
        long long ans = -LINF;

        for (int j = 1; j <= m; j++) {
            vector<long long> ndp(n + 1, -LINF);
            deque<pair<int,long long>> q;
            for (int i = 1; i <= n; i++) {
                if (i - l >= 0) {
                    long long cur = dp[i - l] - pref[i - l];
                    while (q.size() && cur >= q.front().second) q.pop_front();
                    q.push_front({i - l, cur});
                }

                ndp[i] = ndp[i - 1];
                while (q.size() && !((i - r) <= q.back().first && q.back().first <= (i - l))) q.pop_back();
                if (q.size()) {
                    ndp[i] = max(ndp[i], pref[i] + q.back().second);
                }
                if (i == n) ans = max(ans, ndp[i]);
            }
            swap(dp, ndp);
        }
        return ans;
    }
};