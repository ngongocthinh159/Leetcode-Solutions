class Solution {
public:
    vector<vector<int>> dp;
    int dfs(int i, int open, string &s) {
        if (open < 0) return 0;
        if (i == s.size()) {
            return open == 0;
        }
        if (dp[i][open] != -1) return dp[i][open];
        bool res = false;
        if (s[i] == '*') {
            if (open > 0) res = res | dfs(i + 1, open - 1, s);
            res = res | dfs(i + 1, open + 1, s);
            res = res | dfs(i + 1, open, s);
        } 
        if (s[i] == '(') res = res | dfs(i + 1, open + 1, s);
        if (s[i] == ')') res = res | dfs(i + 1, open - 1, s);
        return dp[i][open] = res;
    }
    bool checkValidString(string s) {
        int n = s.size();
        dp.assign(n, vector<int>(n + 1, -1));
        return dfs(0, 0, s);
    }
};