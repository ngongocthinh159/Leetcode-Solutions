#define ll long long
#define N 12
#define M 2005
ll dp[1 << N], median[1 << N], len[1 << N];
int buf[M];
class Solution {
public:
    int top;
    long long minMergeCost(vector<vector<int>>& lists) {
        int n = lists.size();
        for (int mask = 1; mask < (1 << n); mask++) {
            top = 0;
            for (int bit = 0; bit < n; bit++) if ((mask >> bit) & 1)
                for (auto x : lists[bit]) buf[top++] = x;
            sort(buf, buf + top);
            len[mask] = top;
            median[mask] = buf[(top + 1)/2 - 1];
        }
        for (int mask = 1; mask < (1 << n); mask++) if (__builtin_popcount(mask) > 1) {
            dp[mask] = LLONG_MAX;
            for (int submask = mask; ; submask = (submask - 1) & mask) {
                if (submask == mask) continue;

                int submask2 = mask^submask;
                dp[mask] = min(dp[mask], dp[submask] + dp[submask2] + len[submask] + len[submask2] + abs(median[submask] - median[submask2]));

                if (submask == 0) break;
            }
        }
        return dp[(1 << n) - 1];
    }
};