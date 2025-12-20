class Solution {
public:
    vector<vector<int>> g;
    vector<vector<vector<int>>> dp;
    vector<int> ps;
    vector<int> ft;
    int n;
    int B;
    void dfs(int u) {
        vector<int> cdp(B + 1);
        vector<int> cdp2(B + 1);
        vector<int> cdp3(B + 1);
        for (auto v : g[u]) {
            dfs(v);
            vector<int> ndp = cdp;
            vector<int> ndp2 = cdp2;
            for (int tot = 0; tot <= B; tot++) {
                for (int j = 0; j <= tot; j++)
                    ndp[tot] = max(ndp[tot], dp[v][j][0] + cdp[tot - j]);
                for (int j = 0; j <= tot; j++)
                    ndp2[tot] = max(ndp2[tot], dp[v][j][1] + cdp2[tot - j]);
            }
            swap(cdp, ndp);
            swap(cdp2, ndp2);
        }
        for (int tot = 0; tot <= B; tot++) {
            dp[u][tot][0] = cdp[tot];
            if (tot >= ps[u - 1]) 
                dp[u][tot][0] = max(dp[u][tot][0], cdp2[tot - ps[u - 1]] + ft[u - 1] - ps[u - 1]);
            dp[u][tot][1] = cdp[tot];
            if (tot >= ps[u - 1]/2)
                dp[u][tot][1] = max(dp[u][tot][1], cdp2[tot - ps[u - 1]/2] + ft[u - 1] - ps[u - 1]/2);
        }
    }
    int maxProfit(int N, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
        n = N;
        g.resize(n + 1);
        dp.assign(n + 1, vector<vector<int>>(budget + 1, vector<int>(2, -1)));
        ps = present;
        ft = future;
        B = budget;
        for (auto &e : hierarchy)
            g[e[0]].push_back(e[1]);
        dfs(1);
        return dp[1][budget][0];
    }
};