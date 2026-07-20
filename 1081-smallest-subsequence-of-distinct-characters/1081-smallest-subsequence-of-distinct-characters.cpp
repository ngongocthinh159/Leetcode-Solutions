class Solution {
public:
    string smallestSubsequence(string s) {
        string res = "";
        int cnt[26]{};
        int n = s.size();
        for (int i = 0; i < n; i++) cnt[s[i] - 'a']++;
        bool vis[26]{};
        for (int i = 0; i < n; i++) {
            cnt[s[i] - 'a']--;
            if (res.empty()) res += s[i], vis[s[i] - 'a'] = 1;
            else {
                if (vis[s[i] - 'a']) continue;
                while (res.size()) {
                    if (res.back() < s[i]) break;
                    if (cnt[res.back() - 'a'] == 0) break;
                    vis[res.back() - 'a'] = 0;
                    res.pop_back();
                }
                vis[s[i] - 'a'] = 1;
                res += s[i];
            }
        }
        return res;
    }
};