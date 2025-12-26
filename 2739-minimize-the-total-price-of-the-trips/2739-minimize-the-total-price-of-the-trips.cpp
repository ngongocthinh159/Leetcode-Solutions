class Solution {
public:
    vector<vector<int>> g;
    vector<vector<int>> par;
    vector<int> cnt;
    vector<int> depth;
    int n, msb;
    int minimumTotalPrice(int N, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips) {
        n = N;
        g.resize(n);
        for (auto &e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        cnt.assign(n, 0);
        depth.assign(n, 0);
        msb = 32 - __builtin_clz(n) - 1;
        par.assign(msb + 1, vector<int>(n, 0));
        dfs(0, -1);
        for (int j = 1; j <= msb; j++)
            for (int i = 0; i < n; i++) par[j][i] = par[j - 1][par[j - 1][i]];
        for (auto &t : trips) {
            int u = t[0], v = t[1];
            int A = lca(u, v);
            while (u != A) {
                cnt[u]++;
                u = par[0][u];
            }
            while (v != A) {
                cnt[v]++;
                v = par[0][v];
            }
            cnt[A]++;
        }
        for (int i = 0; i < n; i++) price[i] = price[i] * cnt[i];
        return dfs2(0, -1, price).first;
    }
    pair<int,int> dfs2(int u, int p, vector<int> &price) {
        int res0 = 0, res1 = 0;
        int sum0 = 0, sum1 = 0;
        for (auto v : g[u]) if (v != p) {
            auto res = dfs2(v, u, price);
            sum0 += res.first;
            sum1 += res.second;
        }
        res0 = price[u] / 2 + sum1;
        res0 = min(res0, price[u] + sum0);
        res1 = price[u] + sum0;
        return {res0, res1};
    }
    void dfs(int u, int pu) {
        for (auto v : g[u]) if (v != pu) {
            par[0][v] = u;
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }
    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        int k = depth[u] - depth[v];
        for (int bit = msb; bit >= 0; bit--)
            if ((k >> bit) & 1) u = par[bit][u];
        if (u == v) return u;
        for (int bit = msb; bit >= 0; bit--) {
            if (par[bit][u] != par[bit][v]) {
                u = par[bit][u];
                v = par[bit][v];
            }
        }
        return par[0][u];
    }
};