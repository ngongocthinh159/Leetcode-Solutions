class Solution {
public:
    vector<vector<int>> g;
    bool dfs(int u, int tar, vector<bool> &vis) {
        vis[u] = 1;
        if (u == tar) return true;
        for (auto v : g[u]) if (!vis[v]) {
            if (dfs(v, tar, vis)) return true;
        }
        return false;
    }
    vector<bool> checkIfPrerequisite(int n, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        g.resize(n);
        for (auto &p : prerequisites) g[p[0]].push_back(p[1]);
        vector<bool> ans;
        ans.reserve(queries.size());
        for (auto &q : queries) {
            vector<bool> vis(n);
            if (dfs(q[0], q[1], vis)) ans.push_back(true);
            else ans.push_back(false);
        }
        return ans;
    }
};