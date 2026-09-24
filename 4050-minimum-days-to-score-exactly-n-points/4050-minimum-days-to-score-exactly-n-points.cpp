#define N 100005
int dp[N];
auto init = []{
    for (int i = 0; i < N; i++) dp[i] = INT_MAX;
    dp[0] = 0;
    for (int i = 1; i < N; i++) {
        for (int j = 1; j * (j + 1) / 2 <= i; j++) {
            dp[i] = min(dp[i], dp[i - j * (j + 1) / 2] + 1 + j);
        }
    }
    return 0;
}();
class Solution {
public:
    int minDays(int n) {
        return dp[n] - 1;
    }
};