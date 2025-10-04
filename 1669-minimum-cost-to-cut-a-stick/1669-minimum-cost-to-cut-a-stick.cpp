class Solution {
public:
    int minCost(int n, vector<int>& cuts) {
        vector<int> c;
        c.push_back(0);
        c.push_back(n);
        for (auto x : cuts) c.push_back(x);
        sort(c.begin(), c.end());
        n = c.size();
        const int IINF = 1e9 + 5;
        vector<vector<int>> dp(n, vector<int>(n, IINF));
        for (int len = 1; len <= 2; len++)
            for (int i = 0; i + len - 1 < n; i++) dp[i][i + len - 1] = 0;
        for (int len = 3; len <= n; len++)
            for (int i = 0; i + len - 1 < n; i++)
                for (int j = i + 1; j < i + len - 1; j++)
                    dp[i][i + len - 1] = min(dp[i][i + len - 1], c[i + len - 1] - c[i] + dp[i][j] + dp[j][i + len - 1]);
        return dp[0][n - 1];
    }
};