class Solution {
public:
    vector<vector<int>> dp;
    vector<vector<int>> g;
    int k = 21;
    long long ans = 0;
    vector<int> cnt;
    void dfs(int u, int p, vector<int> &group) {
        dp[u][group[u]]++;
        for (auto v : g[u]) if (v != p) {
            dfs(v, u, group);
            for (int i = 1; i < k; i++) {
                ans += 1ll * dp[v][i] * (cnt[i] - dp[v][i]);
                dp[u][i] += dp[v][i];
            }
        }
    }
    long long interactionCosts(int n, vector<vector<int>>& edges, vector<int>& group) {
        dp.assign(n, vector<int>(k));
        g.resize(n);
        cnt.resize(k);
        for (int i = 0; i < n; i++) cnt[group[i]]++;
        for (auto &e : edges) g[e[0]].push_back(e[1]), g[e[1]].push_back(e[0]);
        dfs(0, -1, group);
        return ans;
    }
};