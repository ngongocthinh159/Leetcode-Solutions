
class Solution {
public:
    array<int,3> getmx(int i, int j, string &s) {
        if (s[i] != s[j]) return {0, -1, -1};
        int n = s.size(), cnt = 1;
        while (i - 1 >= 0 && j + 1 < n && s[i - 1] == s[j + 1]) i--, j++, cnt++;
        return {cnt, i, j};
    }
    int almostPalindromic(string s) {
        int n = s.size(), ans = 1;
        for (int i = 0; i < n; i++) {
            auto [cnt, l, r] = getmx(i, i, s);
            if (cnt != 0) {
                ans = max(ans, r - l + 1);
                ans = max(ans, min(n, r - l + 1 + 1));
                if (l - 2 >= 0 && r + 1 < n) {
                    auto [cnt2, l2, r2] = getmx(l - 2, r + 1, s);
                    if (cnt2 != 0) ans = max(ans, r2 - l2 + 1);
                }
                if (l - 1 >= 0 && r + 2 < n) {
                    auto [cnt2, l2, r2] = getmx(l - 1, r + 2, s);
                    if (cnt2 != 0) ans = max(ans, r2 - l2 + 1);
                }
            }
        }
        for (int i = 0; i < n - 1; i ++) {
            auto [cnt, l, r] = getmx(i, i + 1, s);
            if (cnt != 0) {
                ans = max(ans, r - l + 1);
                ans = max(ans, min(n, r - l + 1 + 1));
                if (l - 2 >= 0 && r + 1 < n) {
                    auto [cnt2, l2, r2] = getmx(l - 2, r + 1, s);
                    if (cnt2 != 0) ans = max(ans, r2 - l2 + 1);
                }
                if (l - 1 >= 0 && r + 2 < n) {
                    auto [cnt2, l2, r2] = getmx(l - 1, r + 2, s);
                    if (cnt2 != 0) ans = max(ans, r2 - l2 + 1);
                }
            }
        }
        return ans;
    }
};