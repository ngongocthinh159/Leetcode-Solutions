#define N 105
long long dp[N][N];
class Solution {
public:
    const int MOD = 1e9 + 7;
    int numMusicPlaylists(int n, int goal, int k) {
        dp[0][0] = 1;
        for (int i = 1; i <= goal; i++)
            for (int j = 1; j <= min(n, i); j++) {
                dp[i][j] = dp[i - 1][j] * max(0, j - k) % MOD + dp[i - 1][j - 1] * (n - (j - 1)) % MOD;
                dp[i][j] %= MOD;
            }
        return dp[goal][n];
    }
};