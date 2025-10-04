class Solution {
public:
    unordered_map<int,unordered_map<int,int>> dp;
    vector<int> c;
    int dfs(int st, int end) {
        if (dp[st].count(end)) return dp[st][end];
        int res = INT_MAX;
        auto it1 = lower_bound(c.begin(), c.end(), st);
        auto it2 = upper_bound(c.begin(), c.end(), end);
        while (it1 != it2) {
            if (*it1 != st && *it1 != end)
                res = min(res, end - st + dfs(st, *it1) + dfs(*it1, end));
            ++it1;
        }
        return dp[st][end] = res == INT_MAX ? 0 : res;
    } 
    int minCost(int n, vector<int>& cuts) {
        c = cuts;
        sort(c.begin(), c.end());
        return dfs(0, n);
    }
};