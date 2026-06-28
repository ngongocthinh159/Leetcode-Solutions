class Solution {
public:
    vector<long long> minTimeMaxPower(int n, vector<vector<int>>& edges, int power, vector<int>& cost, int source, int target) {
        vector<vector<pair<long long,long long>>> g(n);
        for (auto &e : edges) {
            g[e[0]].push_back({e[1], e[2]});
        }
        vector<vector<long long>> dist(n, vector<long long>(power + 1, LLONG_MAX));
        dist[source][power] = 0;
        priority_queue<array<long long,3>,vector<array<long long,3>>, greater<>> q;
        q.push({0, source, power});
        while (q.size()) {
            auto tuple = q.top();
            q.pop();
            long long w_u = tuple[0];
            long long u = tuple[1];
            long long power_u = tuple[2];
            if (dist[u][power_u] > w_u) continue;
            if (power_u < cost[u]) continue;
            for (auto &[v, w_uv] : g[u]) {
                int nPower = power_u - cost[u];
                if (dist[v][nPower] > w_u + w_uv) {
                    dist[v][nPower] = w_u + w_uv;
                    q.push({dist[v][nPower], v, nPower});
                }
            }
        }

        long long mnCost = LLONG_MAX;
        for (int i = 0; i <= power; i++) mnCost = min(mnCost, dist[target][i]);
        if (mnCost == LLONG_MAX) return {-1,-1};
        for (int i = power; i >= 0; i--) if (dist[target][i] == mnCost) {
            return {mnCost, i};
        }
        return {-1,-1};
    }
};