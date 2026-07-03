class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();
        int m = edges.size();
        vector<vector<int>> es;
        int mn = INT_MAX;
        int mx = -1;
        for (auto &e : edges) {
            if (!online[e[0]] || !online[e[1]]) continue;
            es.push_back(e);
            mn = min(mn, e[2]);
            mx = max(mx, e[2]);
        }
        if (es.empty()) return -1;
        sort(es.begin(), es.end(), [](auto &a, auto &b) {
            return a[2] > b[2];
        });
        long long l = mn - 1, r = mx + 1;
        while (r - l > 1) {
            long long minThreshold = l + (r - l)/2;
            vector<vector<pair<int,long long>>> g(n);
            for (auto &e : es) {
                if (e[2] < minThreshold) break;
                g[e[0]].push_back({e[1], e[2]});
            }
            vector<long long> dist(n, LLONG_MAX);
            dist[0] = 0;
            priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<>> q;
            q.push({0, 0});
            while (q.size()) {
                auto p = q.top();
                q.pop();
                long long w_u = p.first;
                int u = p.second;
                if (w_u > dist[u]) continue;
                if (u == n - 1) break;
                for (auto &[v, w_uv] : g[u]) if (dist[v] > w_u + w_uv) {
                    dist[v] = w_u + w_uv;
                    q.push({dist[v], v});
                }
            }

            if (dist[n - 1] <= k)
                l = minThreshold;
            else
                r = minThreshold;
        }
        if (l == mn - 1) return -1;
        return l;
    }
};