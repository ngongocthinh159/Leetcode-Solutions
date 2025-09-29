#define N 55
#define minimize(x,y) (x = ((x) < (y) ? (x) : (y)))
int dp[N][N];
class Solution {
public:
    int minScoreTriangulation(vector<int>& values) {
        int n = values.size();
        for (int i = 0; i + 1 < n; i++) dp[i][i + 1] = 0;
        for (int len = 3; len <= n; len++)
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                dp[i][j] = INT_MAX;
                for (int k = i + 1; k < j; k++)
                    minimize(dp[i][j], values[i] * values[j] * values[k] + dp[i][k] + dp[k][j]);
            }
        return dp[0][n - 1];
    }
};