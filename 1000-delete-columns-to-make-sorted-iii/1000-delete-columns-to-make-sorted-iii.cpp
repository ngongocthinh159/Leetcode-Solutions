class Solution {
public:
    int N, n;
    vector<vector<int>> dp;
    int dfs(int i, int last, vector<string> &ss) {
        if (i == n) return 0;
        if (dp[i][last] != -1) return dp[i][last];
        int res;
        if (last == n) {
            res = min(dfs(i + 1, i, ss), 1 + dfs(i + 1, last, ss));
        } else {
            bool canKeep = true;
            for (auto &s : ss) if (s[i] < s[last]) {
                canKeep = false;
                break;
            }
            res = 1 + dfs(i + 1, last, ss);
            if (canKeep) res = min(res, dfs(i + 1, i, ss));
        }
        return dp[i][last] = res;
    }
    int minDeletionSize(vector<string>& strs) {
        N = strs.size();
        n = strs[0].size();
        dp.assign(n, vector<int>(n + 1, -1));
        return dfs(0, n, strs);
    }
};