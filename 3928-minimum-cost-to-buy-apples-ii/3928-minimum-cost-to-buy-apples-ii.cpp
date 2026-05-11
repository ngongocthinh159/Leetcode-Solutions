class Solution {
public:
    vector<long long> dijkstra(int n, int src, vector<vector<pair<int,long long>>> &g) {
        vector<long long> dist(n, LLONG_MAX);
        auto cmp = [&](auto &a, auto &b) {
            return b[1] < a[1];
        };
        priority_queue<array<long long, 2>, vector<array<long long, 2>>, decltype(cmp)> q(cmp);
        q.push({src, 0});
        dist[src] = 0;
        while (q.size()) {
            auto [u, w_u] = q.top();
            q.pop();
            if (dist[u] < w_u) continue;
            for (auto [v, w_uv] : g[u]) {
                if (dist[v] > w_u + w_uv) {
                    dist[v] = w_u + w_uv;
                    q.push({v, dist[v]});
                }
            }
        }
        return dist;
    }
    vector<int> minCost(int n, vector<int>& prices, vector<vector<int>>& roads) {
        vector<long long> ans(n);
        for (int i = 0; i < n; i++) ans[i] = prices[i];
        vector<vector<pair<int, long long>>> g1(n);
        vector<vector<pair<int, long long>>> g2(n);
        for (auto &r : roads) {
            int u = r[0];
            int v = r[1];
            long long cost = r[2];
            long long tax = r[3];
            g1[u].push_back({v, cost});
            g1[v].push_back({u, cost});
            g2[u].push_back({v, cost * tax});
            g2[v].push_back({u, cost * tax});
        }
        vector<vector<long long>> d1(n);
        vector<vector<long long>> d2(n);
        for (int i = 0; i < n; i++) {
            d1[i] = dijkstra(n, i, g1);
            d2[i] = dijkstra(n, i, g2);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) if (j != i) {
                if (d1[i][j] != LLONG_MAX && d2[j][i] != LLONG_MAX)
                    ans[i] = min(ans[i], d1[i][j] + d2[j][i] + prices[j]);
            }
        }
        vector<int> res(n);
        for (int i = 0; i < n; i++) res[i] = ans[i];
        return res;
    }
};