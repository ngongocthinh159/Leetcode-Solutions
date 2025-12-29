class Solution {
public:
    unordered_map<string,unordered_map<string,bool>> dp;
    bool dfs(string &s, string &t, unordered_map<string,vector<char>> &M) {
        int n = s.size();
        if (n == 1) return true;
        if (dp.count(s) && dp[s].count(t)) return dp[s][t];

        
        if (t.size() + 1 == s.size()) {
            string tmp = "";
            return dp[s][t] = dfs(t, tmp, M);
        }

        int idx = t.size();
        if (!M.count(s.substr(idx,2))) {
            return dp[s][t] = false;
        }
        bool res = 0;
        for (auto c : M[s.substr(idx,2)]) {
            t += c;
            res = res | dfs(s, t, M);
            t.pop_back();
            if (res) break;
        }
        return dp[s][t] = res;
    }
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        unordered_map<string,vector<char>> M;
        for (auto &a : allowed) {
            M[a.substr(0, 2)].push_back(a[2]);
        }
        string tmp = "";
        return dfs(bottom, tmp, M);
    }
};