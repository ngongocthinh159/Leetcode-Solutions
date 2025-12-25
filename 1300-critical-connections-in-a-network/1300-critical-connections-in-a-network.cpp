class Solution {
public:
    vector<int> color;
    vector<int> depth;
    vector<vector<int>> g;
    vector<vector<int>> ans;
    int dfs(int u, int p) {
        color[u] = 1;
        int lowu = INT_MAX;
        for (auto v : g[u]) if (v != p) {
            if (color[v] == 0) {
                depth[v] = depth[u] + 1;
                lowu = min(lowu, dfs(v, u));
            } else if (color[v] == 1) {
                lowu = min(lowu, depth[v]);
            }
        }
        if (p != -1 && lowu >= depth[u]) ans.push_back({u, p});
        color[u] = 2;
        return lowu;
    }
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        g.resize(n);
        depth.resize(n);
        color.resize(n);
        for (auto &c : connections) {
            g[c[0]].push_back(c[1]);
            g[c[1]].push_back(c[0]);
        }
        dfs(0, -1);
        return ans;
    }
};