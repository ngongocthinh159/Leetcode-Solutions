long long dp[20][2][2][10];
class Solution {
public:
    pair<int,int> intersect(int x1, int y1, int x2, int y2) {
        if (x1 > y2 || x2 > y1) return {-1, -1};
        return {max(x1, x2), min(y1, y2)};
    }
    long long solve(long long x, int k) {
        string s = to_string(x);
        int n = s.size();
        int b[n + 1];
        for (int i = 1; i <= n; i++) b[i] = s[i - 1] - '0';

        for (int i = 0; i <= n; i++)
            for (int smaller = 0; smaller < 2; smaller++)
                for (int start = 0; start < 2; start++)
                    for (int last = 0; last < 10; last++) dp[i][smaller][start][last] = 0;

        dp[0][0][0][0] = 1;
        for (int i = 0; i < n; i++)
            for (int smaller = 0; smaller < 2; smaller++)
                for (int start = 0; start < 2; start++)
                    for (int last = 0; last < 10; last++) if (dp[i][smaller][start][last]) {
                        int upper = smaller ? 9 : b[i + 1];
                        int lower = 0;
                        int lo = 0, hi = 9;
                        if (start) {
                            lo = max(lo, last - k);
                            hi = min(hi, last + k);
                            auto p = intersect(lower, upper, lo, hi);
                            lower = p.first;
                            upper = p.second;
                        }
                        if (lower == -1) continue;
                        for (int j = lower; j <= upper; j++) {
                            int nsmaller = smaller || j < b[i + 1];
                            int nstart = start || j != 0;
                            int nlast = j;
                            dp[i + 1][nsmaller][nstart][nlast] += dp[i][smaller][start][last];
                        }
                    }

        long long ans = 0;
        for (int smaller = 0; smaller < 2; smaller++)
            for (int last = 0; last < 10; last++) ans += dp[n][smaller][1][last];
        return ans;
    }
    long long goodIntegers(long long l, long long r, int k) {
        return solve(r, k) - solve(l - 1, k);
    }
};