class Solution {
public:
    int longestBalanced(string s) {
        int n = s.size(), ans = 0;
        int cnt[26]{};
        unordered_map<int,int> f;
        for (int i = 0; i < n; i++) {
            f.clear();
            for (int j = i; j >= 0; j--) {
                int idx = s[j] - 'a';
                if (cnt[idx] && --f[cnt[idx]] == 0)
                    f.erase(cnt[idx]);
                cnt[idx]++;
                f[cnt[idx]]++;
                if (f.size() == 1) ans = max(ans, i - j + 1);
            }
            for (int j = i; j >= 0; j--) cnt[s[j] - 'a'] = 0;
        }
        return ans;
    }
};