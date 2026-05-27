class Solution {
public:
    vector<vector<int>> g;
    int n;
    vector<vector<vector<int>>> dp;
    const int MOD = 1e9 + 7;
    void add(int &x, int y) {
        x += y;
        if (x >= MOD) x -= MOD;
    }
    void dfs(int u, int p, vector<int>& nums, int k) {
        dp[u][1][nums[u] % k] = 1;
        for (auto v : g[u]) if (v != p) {
            dfs(v, u, nums, k);
            vector<int> f = dp[u][0]; // not choose
            vector<int> g = dp[u][1]; // choose

            for (int i = 0; i < k; i++) {
                add(f[i], dp[v][0][i]);
                add(f[i], dp[v][1][i]);

                for (int j = 0; j < k; j++) {
                    int x = (i + j) % k;
                    add(g[x], 1ll * dp[u][1][i] * dp[v][0][j] % MOD);

                    add(f[x], 1ll * dp[u][0][i] * dp[v][0][j] % MOD);
                    add(f[x], 1ll * dp[u][0][i] * dp[v][1][j] % MOD);
                }
            }
            
            swap(dp[u][0], f);
            swap(dp[u][1], g);
        }
    }
    int countValidSubsets(vector<int>& parent, vector<int>& nums, int k) {
        n = parent.size();
        g.resize(n);
        dp.assign(n, vector<vector<int>>(2, vector<int>(k)));
        for (int i = 1; i < n; i++) {
            g[i].push_back(parent[i]);
            g[parent[i]].push_back(i);
        }
        dfs(0, -1, nums, k);
        return (dp[0][0][0] + dp[0][1][0]) % MOD;
    }
};