class Solution {
public:
    long long elevatorRequests(int N, int start, vector<vector<int>>& r) {
        int n = r.size();
        int fMask = (1 << n) - 1;
        const long long LINF = 1e15;
        vector<vector<long long>> dp(1 << n, vector<long long>(n, LINF));
        for (int i = 0; i < n; i++) {
            dp[1 << i][i] = max(abs(start - r[i][1]), r[i][0]);
        }
        for (int mask = 1; mask <= fMask; mask++)
            for (int i = 0; i < n; i++) if (((mask >> i) & 1) && dp[mask][i] != LINF) {
                for (int j = 0; j < n; j++) if (!((mask >> j) & 1)) {
                    int nmask = mask | (1 << j);
                    dp[nmask][j] = min(dp[nmask][j], max(dp[mask][i] + abs(r[i][1] - r[j][1]), 1LL * r[j][0]));
                }
            }
        long long ans = LINF;
        for (int i = 0; i < n; i++) ans = min(ans, dp[fMask][i]);
        return ans;
    }
};