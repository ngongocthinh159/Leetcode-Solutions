/*
    We need to proof that: If we concatinate two strings, we always try to use the max matching of 1st surfix and 2nd prefix
    
    + So if we look at the optimal solution, it will look like:
        s1        e1
            s2      e2
                s3      e3
                    s4      e4

        That is the s(i + 1) > si && e(i + 1) > ei. It look like this because no word is substring of another word (in the final string, there is no same starting point or no same ending point). 
        
        Imagine if we not choose max matching of e1 and s2 (assume that there is multiple matching position of e1 and s2), which mean we still can shift all s2, s3, s4 to the left to reduce the total length, because we can shift s2, and s3 only depend on s2, then we can shift s3 and so on..
*/

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