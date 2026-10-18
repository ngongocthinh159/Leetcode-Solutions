#define N 1005
bitset<N> prime;
int top = 0;
int buf[N];
auto init = [] {
    prime.flip();
    for (int i = 2; i < N; i++) if (prime[i]) {
        buf[top++] = i;
        for (int j = i * i; j < N; j += i) prime[j] = 0;
    }
    return false;
}();
class Solution {
public:
    vector<int> maxPrimeSubset(int n, int s) {
        if (n == 1) return {};
        int sz = upper_bound(buf, buf + top, n) - buf;
        vector<int> p(sz);
        for (int i = 0; i < sz; ++i) p[i] = buf[i];
        reverse(p.begin(), p.end());
        vector<vector<int>> dp(sz + 1, vector<int>(s + 1, INT_MAX));
        dp[0][0] = 0;
        for (int i = 0; i < sz; ++i)
            for (int j = 0; j <= s; j++) if (dp[i][j] != INT_MAX) {
                dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
                if (j + p[i] <= s) dp[i + 1][j + p[i]] = dp[i][j] + 1;
            }
        int len = -1, sum = -1;
        for (int j = s; j >= 0; j--) if (dp[sz][j] != INT_MAX) {
            sum = j;
            len = dp[sz][j];
            break;
        }
        if (sum == -1) return {};
        vector<int> res;
        for (int i = sz; i >= 1; --i) {
            int val = p[i - 1];
            if (val <= sum && dp[i - 1][sum - val] == (len - 1)) {
                len--;
                sum -= val;
                res.push_back(val);
            }
        }
        return res;
    }
};