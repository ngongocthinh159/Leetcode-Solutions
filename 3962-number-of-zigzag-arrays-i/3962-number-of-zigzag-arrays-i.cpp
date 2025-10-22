#define N 2005
int dp[N][N][3];
class Solution {
public:
    const int MOD = 1e9 + 7;
    void add(int &x, int y) {
        x += y;
        if (x >= MOD) x -= MOD;
        if (x < 0) x += MOD;
    }
    int zigZagArrays(int n, int l, int r) {
        for (int i = 0; i < n; i++)
            for (int j = l - 1; j <= r; j++)
                for (int k = 0; k < 3; k++)
                    dp[i][j][k] = 0;

        for (int i = l; i <= r; i++) dp[0][i][0] = 1;
        for (int i = 0; i < n - 1; i++) {
            for (int j = l; j <= r; j++) {
                for (int k = 0; k < 3; k++) {
                    if (k == 0) {
                        if (j + 1 <= r) {
                            add(dp[i + 1][j + 1][1], dp[i][j][k]);
                            add(dp[i + 1][r + 1][1], -dp[i][j][k]);
                        }
                        if (j - 1 >= l) {
                            add(dp[i + 1][l][2], dp[i][j][k]);
                            add(dp[i + 1][j][2], -dp[i][j][k]);
                        }
                    } else if (k == 1) {
                        if (j - 1 >= l) {
                            add(dp[i + 1][l][2], dp[i][j][k]);
                            add(dp[i + 1][j][2], -dp[i][j][k]);
                        }
                    } else {
                        if (j + 1 <= r) {
                            add(dp[i + 1][j + 1][1], dp[i][j][k]);
                            add(dp[i + 1][r + 1][1], -dp[i][j][k]);
                        }
                    }
                }
            }
            for (int j = l; j <= r; j++) 
                for (int k = 0; k < 3; k++)
                    add(dp[i + 1][j][k], dp[i + 1][j - 1][k]); 
        }
        int ans = 0;
        for (int i = l; i <= r; i++) 
            for (int k = 0; k < 3; k++)
                add(ans, dp[n - 1][i][k]);
        return ans;
    }
};