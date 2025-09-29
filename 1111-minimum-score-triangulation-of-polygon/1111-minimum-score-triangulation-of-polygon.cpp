#define N 55
#define minimize(x,y) (x = ((x) < (y) ? (x) : (y)))
int dp[N][N];
class Solution {
public:
    int dfs(int st, int end, vector<int> &v) {
        if (end - st + 1 <= 2) return 0;
        if (dp[st][end] != -1) return dp[st][end];
        int res = INT_MAX;
        for (int k = st + 1; k < end; k++)
            minimize(res, v[st] * v[end] * v[k] + dfs(st, k, v) + dfs(k, end, v));
        return dp[st][end] = res;
    }
    int minScoreTriangulation(vector<int>& values) {
        int n = values.size();
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) dp[i][j] = -1;
        return dfs(0, n - 1, values);
    }
};