#define ll long long
#define N 12
ll dp[1 << N], median[1 << N], len[1 << N];
class Solution {
public:
    void merge(vector<int>&a, vector<int>&b) {
        int n = a.size(), m = b.size();
        vector<int> c(n + m);
        int i = 0, j = 0, k = 0;
        while (i < n && j < m) {
            if (a[i] <= b[j]) c[k++] = a[i++];
            else c[k++] = b[j++];
        }
        while (i < n) c[k++] = a[i++];
        while (j < m) c[k++] = b[j++];
        swap(a, c);
    }
    long long minMergeCost(vector<vector<int>>& lists) {
        int n = lists.size();
        for (int mask = 1; mask < (1 << n); mask++) {
            int clen = 0, cmedian = 0;
            vector<int> cur;
            for (int bit = 0; bit < n; bit++) if ((mask >> bit) & 1) {
                merge(cur, lists[bit]), clen += (int) lists[bit].size();
            }
            cmedian = cur[(clen + 1)/2 - 1];
            len[mask] = clen;
            median[mask] = cmedian;
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