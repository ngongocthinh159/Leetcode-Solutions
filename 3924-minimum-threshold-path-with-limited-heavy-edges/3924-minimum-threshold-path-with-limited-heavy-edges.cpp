class Solution {
public:
    bool ok(int n, vector<vector<pair<int,int>>> &g, int source, int target, int k, int H) {
        vector<int> dist(n, INT_MAX);
        deque<pair<int,int>> q;
        q.push_back({source, 0});
        dist[source] = 0;
        while (q.size()) {
            auto [u, w_u] = q.front();
            q.pop_front();
            for (auto [v, w_uv] : g[u]) {
                int cost = w_uv > H;
                if (dist[v] > cost + w_u) {
                    dist[v] = cost + w_u;
                    if (cost == 0) {
                        q.push_front({v, dist[v]});
                    } else {
                        q.push_back({v, dist[v]});
                    }
                }
            }
        }

        return dist[target] <= k;
    }
    int minimumThreshold(int n, vector<vector<int>>& edges, int source, int target, int k) {
        vector<vector<pair<int,int>>> g(n);
        for (auto &e : edges) {
            g[e[0]].push_back({e[1], e[2]});
            g[e[1]].push_back({e[0], e[2]});
        }
        int l = -1, r = 1e9 + 5;
        while (r - l > 1) {
            int m = l + (r - l)/2;
            if (ok(n, g, source, target, k, m))
                r = m;
            else
                l = m;
        }
        return r == 1e9 + 5 ? -1 : r;
    }
};