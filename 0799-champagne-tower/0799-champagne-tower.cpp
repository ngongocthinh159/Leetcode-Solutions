#define N 105
double dp[N];
class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        dp[0] = poured;
        for (int i = 1; i <= query_row; i++) {
            for (int j = i; j >= 0; j--) {
                if (j == 0) dp[j] = max(0.0, dp[j] - 1) / 2.0;
                else if (j == i) dp[j] = max(0.0, dp[j - 1] - 1) / 2.0;
                else dp[j] = max(0.0, dp[j - 1] - 1) / 2.0 + max(0.0, dp[j] - 1) / 2.0;
            }
        }
        return min(dp[query_glass], 1.00);
    }
};