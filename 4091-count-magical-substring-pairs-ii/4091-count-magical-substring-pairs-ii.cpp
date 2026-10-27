class Solution {
public:
    long long countMagicalPairs(string s) {
        int n = s.size();
        long long ans = 0;
        bool vis1[26], vis2[26];
        vector<vector<int>> prv(n, vector<int>(26));
        vector<vector<int>> nxt(n, vector<int>(26));
        for (int i = 0; i < n; ++i)
            for (int c = 0; c < 26; ++c) prv[i][c] = (c == s[i] - 'a' ? i : (i - 1 >= 0 ? prv[i - 1][c] : -1));
        for (int i = n - 1; i >= 0; --i)
            for (int c = 0; c < 26; ++c) nxt[i][c] = (c == s[i] - 'a' ? i : (i + 1 < n ? nxt[i + 1][c] : n));
        for (int j = 0; j < n - 1; ++j) {
            for (int c = 0; c < 26; ++c) vis1[c] = vis2[c] = 0;
            vis1[s[j] - 'a'] = 1;
            vis2[s[j + 1] - 'a'] = 1;
            int end1 = j, start2 = j + 1;
            while (end1 != -1 && start2 != n) {
                int mx1 = -1, mn2 = n;
                for (int c = 0; c < 26; ++c) {
                    if (!vis1[c]) mx1 = max(mx1, prv[end1][c]);
                    if (!vis2[c]) mn2 = min(mn2, nxt[start2][c]);
                }
                ans += 1ll * (end1 - mx1) * (mn2 - start2);
                if (mx1 != -1) vis1[s[mx1] - 'a'] = 1;
                if (mn2 != n) vis2[s[mn2] - 'a'] = 1;
                end1 = mx1;
                start2 = mn2;
            }
        }
        return ans;
    }
};