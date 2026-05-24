class Solution {
public:
    vector<int> dp;
    int n;
    int dfs(int i, int d, vector<int> &arr) {
        if (dp[i] != -1) return dp[i];
        int res = 1;
        for (int j = i + 1; j <= min(i + d, n - 1); j++) {
            if (arr[i] > arr[j]) {
                res = max(res, 1 + dfs(j, d, arr));
            } else
                break;
        }
        for (int j = i - 1; j >= max(0, i - d); j--) {
            if (arr[i] > arr[j]) {
                res = max(res, 1 + dfs(j, d, arr));
            } else
                break;
        }
        return dp[i] = res;
    }
    int maxJumps(vector<int>& arr, int d) {
        n = arr.size();
        dp.assign(n, -1);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, dfs(i, d, arr));
        }
        return ans;
    }
};