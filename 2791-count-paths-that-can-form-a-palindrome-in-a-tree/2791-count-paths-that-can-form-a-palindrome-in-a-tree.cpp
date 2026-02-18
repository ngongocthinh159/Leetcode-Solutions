#define N 100005
int buf[N];
class Solution {
public:
    vector<vector<pair<int,int>>> g;
    int n, top;
    long long ans = 0;
    unordered_map<int,int> f;
    vector<int> child;
    vector<bool> del;
    long long countPalindromePaths(vector<int>& parent, string s) {
        n = parent.size();
        g.resize(n + 1);
        child.resize(n + 1);
        del.resize(n + 1);
        s = "#" + s;
        for (int i = 1; i < n; i++) {
            int v = i + 1;
            int u = parent[i] + 1;
            int w = 1 << (s[v] - 'a');
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }
        CD(1, 0);
        return ans;
    }
    int dfs(int u, int p) {
        child[u] = 1;
        for (auto &[v, w] : g[u]) if (v != p && !del[v])
            child[u] += dfs(v, u);
        return child[u];
    }
    int find_centroid(int u, int p, int sz) {
        for (auto &[v, w] : g[u]) if (v != p && !del[v] && child[v] > sz/2)
            return find_centroid(v, u, sz);
        return u;
    }
    void acc_ans(int u, int p, int wu) {
        int cnt = __builtin_popcount(wu);
        if (f.find(wu) != f.end()) ans += f[wu];
        for (int i = 0; i < 26; i++) {
            int nmask = wu ^ (1 << i);
            if (f.find(nmask) != f.end()) ans += f[nmask];
        }

        buf[top++] = wu;
        for (auto &[v, w] : g[u]) if (v != p && !del[v])
            acc_ans(v, u, wu ^ w);
    }
    void CD(int u, int p) {
        int sz = dfs(u, p);
        u = find_centroid(u, p, sz);

        f.clear();
        f.reserve(2*sz);
        f[0]++;
        for (auto &[v, w] : g[u]) if (v != p && !del[v]) {
            top = 0;
            acc_ans(v, u, w);

            for (int i = 0; i < top; i++) f[buf[i]]++;
        }

        del[u] = 1;        
        for (auto &[v, w] : g[u]) if (v != p && !del[v])
            CD(v, u);
    }
};