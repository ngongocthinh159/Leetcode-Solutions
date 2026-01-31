#define ll long long
#define N 1005
const ll base = 32;
const int MOD = 1e9 + 7;
ll toHash1[N][N], toHash2[N][N], dp[N], arr[N];
bool same[N][N];
const ll SEN = 9e15;
class Solution {
public:
    unordered_map<ll,vector<pair<ll,ll>>> g;
    unordered_map<ll,ll> dijk(ll src) {
        unordered_map<ll,ll> dist;
        dist[src] = 0;
        priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<>> q;
        q.push({0, src});
        while (q.size()) {
            auto [w_u, u] = q.top();
            q.pop();
            if (w_u > dist[u]) continue;
            for (auto [v, w_uv] : g[u]) if (!dist.count(v) || dist[v] > w_u + w_uv) {
                dist[v] = w_u + w_uv;
                q.push({dist[v], v});
            }
        }
        return dist;
    }
    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) {
        int n = source.size(), m = original.size();
        unordered_map<ll,unordered_map<ll,ll>> dist;
        for (int i = 0; i < m; i++) {
            ll u = 0, v = 0;
            bool ok = true;
            for (int j = 0; j < original[i].size(); j++) {
                u = u * base % MOD + (original[i][j] - 'a' + 1);
                if (u >= MOD) u -= MOD;
                v = v * base % MOD + (changed[i][j] - 'a' + 1);
                if (v >= MOD) v -= MOD;
            }
            g[u].push_back({v, cost[i]});
            arr[i] = u;
        }
        for (int r = 0, l = 0; r < n; r++) {
            if (target[r] != source[r]) l = r + 1;
            for (int j = 0; j <= r; j++) {
                same[j][r] = j >= l;
            }
        }
        for (int i = 0; i < m; i++)
            dist[arr[i]] = dijk(arr[i]);
        for (int i = n - 1; i >= 0; i--) {
            ll u = 0, v = 0;
            for (int j = i; j < n; j++) {
                u = u * base % MOD + (source[j] - 'a' + 1);
                if (u >= MOD) u -= MOD;
                v = v * base % MOD + (target[j] - 'a' + 1);
                if (v >= MOD) v -= MOD;
                toHash1[i][j] = u;
                toHash2[i][j] = v;
            }
        }
        for (int i = 0; i < n; i++) dp[i] = SEN;
        dp[n] = 0;
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 1; j <= n; j++) if (dp[j] != SEN) {
                ll cost = -1;
                if (same[i][j - 1]) cost = 0;
                else {
                    ll u = toHash1[i][j - 1], v = toHash2[i][j - 1];
                    if (dist.count(u) && dist[u].count(v)) cost = dist[u][v];
                }
                if (cost != -1)
                    dp[i] = min(dp[i], dp[j] + cost);
            }
        }
        return dp[0] == SEN ? -1 : dp[0];
    }
};