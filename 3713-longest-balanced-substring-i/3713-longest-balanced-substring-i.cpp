class Solution {
public:
    int longestBalanced(string s) {
        int n = s.size(), ans = 0;
        int cnt[26]{};
        for (int i = 0; i < n; i++) {
            int u = 0, mx = -1;
            for (int j = i; j >= 0; j--) {
                int idx = s[j] - 'a';
                if (++cnt[idx] == 1) u++;
                mx = max(mx, cnt[idx]);
                if ((i - j + 1) % u == 0 && (i - j + 1)/u == mx) ans = max(ans, i - j + 1);
            }
            for (int i = 0; i < 26; i++) cnt[i] = 0;
        }
        return ans;
    }
};