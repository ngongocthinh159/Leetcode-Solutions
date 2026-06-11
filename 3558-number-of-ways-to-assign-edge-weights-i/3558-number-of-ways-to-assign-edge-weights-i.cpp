#define ll long long
#define N 100005
const int MOD = 1e9 + 7;
ll expo(ll a, ll b) {
    ll res = 1;
    ll cur = a;
    while (b) {
        if (b&1) res = res * cur % MOD;
        cur = cur * cur % MOD;
        b >>= 1;
    }
    return res;
}
class Solution {
public:
    vector<vector<int>> g;
    void dfs(int u, int p, int cur_d, int &d) {
        d = max(d, cur_d);
        for (auto v : g[u]) if (v != p)
            dfs(v, u, cur_d + 1, d);
    }
    int assignEdgeWeights(vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        g.resize(n);
        for (auto & e : edges) {
            g[e[0] - 1].push_back(e[1] - 1);
            g[e[1] - 1].push_back(e[0] - 1);
        } 
        int d = -1;
        dfs(0, -1, 0, d);
        if (d == 0) return 0;
        return expo(2, d - 1) % MOD;
    }
};