class Solution {
public:
    vector<vector<int>> g;
    long long res;
    long long  dfs(int u, int p, vector<int> &baseTime) {
        long long e = LLONG_MAX;
        long long l = LLONG_MIN;
        for (auto v : g[u]) if (v != p) {
            auto p = dfs(v, u, baseTime);
            e = min(e, p);
            l = max(l, p);
        }
        long long fin = (e != LLONG_MAX ? (2 * l - e) : 0) + baseTime[u];
        return fin;
    }
    long long finishTime(int n, vector<vector<int>>& edges, vector<int>& baseTime) {
        g.resize(n);
        for (auto &e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        return dfs(0, -1, baseTime);
    }
};