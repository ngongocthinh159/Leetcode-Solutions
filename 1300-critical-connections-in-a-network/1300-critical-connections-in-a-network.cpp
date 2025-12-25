class Solution {
public:
    vector<int> dp;
    vector<int> color;
    vector<int> up;
    vector<int> down;
    vector<vector<int>> g;
    vector<vector<int>> ans;
    void dfs(int u, int p, vector<vector<int>> &e) {
        color[u] = 1;
        int sumc = 0;
        for (auto idx : g[u]) {
            int v = e[idx][0] ^ e[idx][1] ^ u;
            if (v != p) {
                if (color[v] == 1) {
                    up[u]++;
                    down[v]++;
                } else if (color[v] == 0) {
                    dfs(v, u, e);
                    sumc += dp[v];
                    if (dp[v] == 0) ans.push_back({u, v});
                }
            }
        }
        dp[u] = up[u] - down[u] + sumc;
        color[u] = 2;
    }
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        dp.resize(n);
        color.resize(n);
        up.resize(n);
        down.resize(n);
        g.assign(n, vector<int>());
        for (int i = 0; i < connections.size(); i++) {
            auto &c = connections[i];
            g[c[0]].push_back(i);
            g[c[1]].push_back(i);
        }
        dfs(0, -1, connections);
        return ans;
    }
};