class Solution {
public:
    vector<vector<pair<int,int>>> g;
    vector<int> ans;
    bool dfs(int u, int p, int idx, string &start, string &target) {
        bool flip = false;
        for (auto [v, eidx] : g[u]) if (v != p) {
            flip ^= dfs(v, u, eidx, start, target);
        }
        bool dif = start[u] != target[u];
        if (dif ^ flip) ans.push_back(idx);
        return dif ^ flip;
    }
    vector<int> minimumFlips(int n, vector<vector<int>>& edges, string start, string target) {
        int idx = 0;
        g.resize(n);
        for (auto &e : edges) {
            g[e[0]].push_back({e[1], idx});
            g[e[1]].push_back({e[0], idx++});
        }
        dfs(0, -1, -1, start, target);
        if (ans.size() && ans.back() == -1) return {-1};
        sort(ans.begin(), ans.end());
        return ans;
    }
};