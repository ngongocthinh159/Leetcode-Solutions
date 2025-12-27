class Solution {
public:
    vector<int> kmp(string &s) {
        int n = s.size();
        vector<int> pref(n);
        for (int i = 1, j = 0; i < n; i++) {
            while (j > 0 && s[i] != s[j]) j = pref[j - 1];
            pref[i] = s[i] == s[j] ? ++j : 0;
        }
        return pref;
    }
    int cal_w(string &s, string &t) {
        string u = t + "#" + s;
        return kmp(u)[u.size() - 1];
    }
    bool maximize(int &x, int y) {
        if (x < y) {
            x = y;
            return true;
        }
        return false;
    }
    string shortestSuperstring(vector<string>& words) {
        int n = words.size();
        const int IINF = 1e9;
        vector<vector<int>> overlap(n, vector<int>(n));
        vector<vector<pair<int,int>>> g(n);
        for (int i = 0; i < n; i++)
            for(int j = 0; j < n; j++) if (i != j) {
                overlap[i][j] = cal_w(words[i], words[j]);
                g[i].push_back({j, overlap[i][j]});
            }
        vector<vector<int>> dp(1 << n, vector<int>(n, -IINF));
        vector<vector<pair<int,int>>> trace(1 << n, vector<pair<int,int>>(n));
        for (int i = 0; i < n; i++) dp[1 << i][i] = 0;
        for (int mask = 0; mask < (1 << n); mask++)
            for (int u = 0; u < n; u++) if (dp[mask][u] != -IINF)
                for (auto [v, w_uv] : g[u]) if (!((mask >> v) & 1)) {
                    if (maximize(dp[mask | (1 << v)][v], dp[mask][u] + w_uv))
                        trace[mask | (1 << v)][v] = {u, mask};
                }
        int mx = -IINF, u;
        int fmask = (1 << n) - 1;
        for (int i = 0; i < n; i++) if (maximize(mx, dp[fmask][i]))
            u = i;
        int e = n - 1;
        int cmask = fmask;
        vector<int> v;
        v.push_back(u);
        while (e--) {
            auto p = trace[cmask][u];
            tie(u, cmask) = p;
            v.push_back(u);
        }
        reverse(v.begin(), v.end());
        string res = "";
        for (int i = 0; i < n; i++) {
            if (i == 0) 
                res += words[v[i]];
            else {
                int len = overlap[v[i - 1]][v[i]];
                res += words[v[i]].substr(len);
            }
        }
        return res;
    }
};