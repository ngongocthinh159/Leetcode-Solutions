#define ll long long
const ll INF = 1e12;
class Solution {
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        sort(factory.begin(), factory.end());
        sort(robot.begin(), robot.end());
        vector<int> fact;
        for (auto& f : factory)
            for (int i = 0; i < f[1]; i++) fact.push_back(f[0]);

        int n = robot.size();
        int m = fact.size();
        // dp[i][j]: min dist if only fix first (i - 1) robots and use first (j - 1) factories (1-based index)
        vector<vector<ll>> dp(n + 5, vector<ll>(m + 5, INF));
        for (int j = 1; j <= m - n + 1; j++) {
            dp[1][j] = 0;
        }
        for (int i = 1; i <= n + 4; i++) {
            for (int j = 1; j <= m + 4; j++) {
                if (dp[i][j] != INF) {
                    if (m - j > n - i) dp[i][j + 1] = min(dp[i][j + 1], dp[i][j]);
                    if (i - 1 < n && j - 1 < m) dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + abs(robot[i - 1] - fact[j - 1]));  
                }
            }
        }
        return dp[n + 1][m + 1];
    }
};