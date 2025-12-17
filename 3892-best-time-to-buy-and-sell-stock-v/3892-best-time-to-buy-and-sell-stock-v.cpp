class Solution {
public:
    int K;
    int n;
    const long long LINF = 1e18 + 5;
    vector<int> v;
    vector<vector<vector<long long>>> dp;
    long long dfs(int i, int k, int t) {
        if (k > K) return -LINF;
        if (i == n) {
            if (t != 0) return -LINF;
            return 0;
        }
        if (dp[i][k][t] != -1) return dp[i][k][t];
        long long res = 0;
        if (t == 0) {
            res = max(-v[i] + dfs(i + 1, k + 1, 1), v[i] + dfs(i + 1, k + 1, 2));
            res = max(res, dfs(i + 1, k, t));
        } else if (t == 1) {
            res = max(dfs(i + 1, k, t), v[i] + dfs(i + 1, k, 0));
        } else {
            res = max(dfs(i + 1, k, t), -v[i] + dfs(i + 1, k, 0));
        }
        return dp[i][k][t] = res;
    }
    long long maximumProfit(vector<int>& prices, int k) {
        K = k;
        n = prices.size();
        v = prices;
        dp.assign(n, vector<vector<long long>>(n / 2 + 5, vector<long long>(3, -1)));
        return dfs(0, 0, 0);
    }
};