class Solution {
public:
    int res = 0;
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        int n = s1.size(), m = s2.size();
        vector<array<int,2>> dp(m);
        vector<vector<array<int,2>>> g(m);
        for (int j = 0; j < m; j++) {
            int cnt = 0;
            int k = j;
            for (int i = 0; i < n; i++) {
                if (s1[i] == s2[k]) {
                    k++;
                    k %= m;
                    if (k == 0) cnt++;
                }
            }
            g[j].push_back({k, cnt});
            // cout << j << ' ' << k << ' ' << cnt << '\n';
        }
        vector<int> color(m, 0);
        vector<int> pref(m);
        vector<int> d(m);
        dfs(0, color, g, pref, d, n1);
        return res / n2;
    }
    void dfs(int u, vector<int> &color, 
    vector<vector<array<int,2>>> &g, 
    vector<int> &pref, vector<int> &d, 
    int mxd) {
        color[u] = 1;
        for (auto &[v, w] : g[u]) {
            if (color[v] == 0) {
                pref[v] = pref[u] + w;
                d[v] = d[u] + 1;
                if (d[v] <= mxd)
                    dfs(v, color, g, pref, d, mxd);
                else {
                    res = pref[u];
                }
            } else if (color[v] == 1) {
                if (d[u] + 1 <= mxd) {
                    int cycleLen = d[u] + 1 - d[v];
                    int cycleSum = w + pref[u] - pref[v];
                    int cycles = (mxd - d[v]) / cycleLen;
                    res = pref[v] + cycles * cycleSum;
                    int remain = mxd - d[v] - cycles * cycleLen;
                    int x = v;
                    while (remain--) {
                        int nxt = g[x][0][0];
                        res += pref[nxt] - pref[x];
                        x = nxt;
                    }
                } else {
                    res = pref[u];
                }
            }
        }

        color[u] = 2;
    }
};