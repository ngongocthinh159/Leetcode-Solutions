int dp[50005][55];
class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        vector<vector<pair<int,int>>> g(n);
        for (auto &e : edges) {
            g[e[0]].push_back({e[1],e[2]});
        }

        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= k; j++) dp[i][j] = INT_MAX;

        dp[0][1] = 0;
        set<array<int,3>> S;
        S.insert({0, 0, 1});
        while (S.size()) {
            auto a = *S.begin();
            S.erase(S.begin());
            int w_u = a[0];
            int u = a[1];
            int repeat = a[2];

            if (w_u > dp[u][repeat]) continue;

            for (auto [v, w_uv] : g[u]) {
                int nrepeat = (labels[v] == labels[u]) ? repeat + 1 : 1;
                int nc = labels[v] - 'a';
                if (nrepeat > k) continue;
                if (dp[v][nrepeat] > w_u + w_uv) {
                    S.erase({dp[v][nrepeat], v, nrepeat});
                    dp[v][nrepeat] = w_u + w_uv;
                    S.insert({dp[v][nrepeat], v, nrepeat});
                }
            }
        }
        int ans = INT_MAX;
        for (int i = 1; i <= k; i++) ans = min(ans, dp[n - 1][i]);
        return ans == INT_MAX ? -1 : ans;
    }
};