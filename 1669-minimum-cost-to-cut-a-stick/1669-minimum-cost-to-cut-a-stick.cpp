class Solution {
public:
    vector<vector<int>> dp;
    vector<int> c;
    int dfs(int st, int end) {
        if (end - st - 1 <= 0) return 0;
        if (dp[st][end] != -1) return dp[st][end];
        int res = INT_MAX;
        for (int i = st + 1; i < end; i++) {
            res = min(res, c[end] - c[st] + dfs(st, i) + dfs(i, end));
        }
        return dp[st][end] = res;
    } 
    int minCost(int n, vector<int>& cuts) {
        c.push_back(0);
        c.push_back(n);
        for (auto x : cuts) c.push_back(x);
        sort(c.begin(), c.end());
        n = c.size();
        dp.assign(n, vector<int>(n, -1));
        return dfs(0, n - 1);
    }
};