class Solution {
public:
    vector<int> lowlink;
    vector<int> color;
    vector<int> depth;
    vector<vector<int>> g;
    vector<vector<int>> ans;
    void dfs(int u, int p) {
        color[u] = 1;
        for (auto v : g[u]) if (v != p) {
            if (color[v] == 0) {
                depth[v] = depth[u] + 1;
                dfs(v, u);
                lowlink[u] = min(lowlink[u], lowlink[v]);
            } else if (color[v] == 1) {
                lowlink[u] = min(lowlink[u], depth[v]);
            }
        }
        if (p != -1 && lowlink[u] >= depth[u]) ans.push_back({u, p});
        color[u] = 2;
    }
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        lowlink.assign(n, INT_MAX);
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