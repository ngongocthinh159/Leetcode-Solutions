#define B 50
#define ll long long
class Solution {
public:
    long long nthSmallest(long long n, int k) {
        vector<vector<ll>> dp(B, vector<ll>(k + 1));
        for (int i = 0; i < B; i++) dp[i][0] = 1;
        dp[0][1] = 1;
        for (int i = 1; i < B; i++)
            for (int j = 1; j <= k; j++) {
                dp[i][j] += dp[i - 1][j];
                dp[i][j] += dp[i - 1][j - 1];
            }
        int o = k;
        long long res = 0;
        for (int i = B - 1; i > 0 && o; i--) {
            if (dp[i - 1][o] < n) {
                n -= dp[i - 1][o];
                o--;
                res ^= (1LL << i);
            }
        }
        if (o) res ^= (1LL << 0);
        return res;
    }
};