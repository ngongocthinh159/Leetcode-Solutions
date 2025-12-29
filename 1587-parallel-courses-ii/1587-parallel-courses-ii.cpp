#define N 15
int dp[1 << N], precourse[N], premask[1 << N];
class Solution {
public:
    void clean(int n) {
        for (int mask = 0; mask < (1 << n); mask++) dp[mask] = INT_MAX, premask[mask] = 0;
        for (int i = 0; i < n; i++) precourse[i] = 0;
    }
    int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
        clean(n);

        vector<vector<int>> g(n);
        for (auto &e : relations) {
            int u = e[0] - 1;
            int v = e[1] - 1;
            precourse[v] |= (1 << u);
        }
        for (int mask = 0; mask < (1 << n); mask++)
            for (int i = 0; i < n; i++) if ((mask >> i) & 1) premask[mask] |= precourse[i];
        int fmask = (1 << n) - 1;
        dp[fmask] = 0;
        for (int mask = fmask; mask >= 0; mask--) if (dp[mask] != INT_MAX) {
            for (int submask = mask; ; submask = (submask - 1) & mask) {
                if (__builtin_popcount(mask ^ submask) <= k && (premask[mask ^ submask] & mask) == 0)
                    dp[submask] = min(dp[submask], dp[mask] + 1);

                if (submask == 0) break;
            }
        }
        return dp[0];
    }
};