class Solution {
public:
    vector<vector<vector<int>>> dp;
    int removeBoxes(vector<int>& boxes) {
        int n = boxes.size();
        dp = vector<vector<vector<int>>>(n, 
            vector<vector<int>>(n,
                vector<int>(n, -1)));
        return dfs(0, n - 1, 0, boxes);
    }
    int dfs(int l, int r, int k, vector<int>& b) {
        if (l > r) return 0;
        if (dp[l][r][k] != -1) return dp[l][r][k];

        int res = (k + 1) * (k + 1) + dfs(l + 1, r, 0, b);
        for (int i = l + 1; i <= r; ++i) if (b[i] == b[l]) {
            res = max(res, dfs(i, r, k + 1, b) + dfs(l + 1, i - 1, 0, b));
        }

        return dp[l][r][k] = res;
    }
};