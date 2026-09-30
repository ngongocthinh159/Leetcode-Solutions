class Solution {
public:
    vector<vector<long long>> dp;
    long long dfs(int i, int first, vector<vector<int>> &meetings) {
        if (i == meetings.size()) {
            if (first) return LLONG_MIN;
            return 0;
        }
        if (dp[i][first] != -1) return dp[i][first];

        long long res = LLONG_MIN;
        // not choose
        res = max(res, dfs(i + 1, first, meetings));

        // choose
        long long cost = first ? (-meetings[i][1]) : (meetings[i][0] - meetings[i][1]);
        int l = i, r = meetings.size();
        while (r - l > 1) {
            int m = l + (r - l)/2;
            if (meetings[m][0] >= meetings[i][1])
                r = m;
            else
                l = m;
        }
        res = max(res, cost + dfs(r, 0, meetings) + meetings[i][2]);
        if (!first) {
            res = max(res, 1ll * meetings[i][0] + meetings[i][2]);
        }

        return dp[i][first] = res;
    }
    long long maxEarnings(vector<vector<int>>& meetings) {
        int n = meetings.size();
        dp.assign(n, vector<long long>(2, -1));
        sort(meetings.begin(), meetings.end());
        long long res =  dfs(0, 1, meetings);
        for (auto &m : meetings) res = max(res, 1ll * m[2]);
        return res;
    }
};