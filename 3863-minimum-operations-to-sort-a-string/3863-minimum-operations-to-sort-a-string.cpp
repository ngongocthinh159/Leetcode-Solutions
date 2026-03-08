class Solution {
public:
    bool isSorted(const string &s) {
        int n = s.size();
        bool ok = true;
        for (int i = 1; i < n; i++) {
            if (s[i] < s[i - 1]) {
                return false;
            }
        }
        return true;
    }
    int minOperations(string s) {
        int n = s.size();
        if (isSorted(s)) return 0;
        if (n == 2)
            return isSorted(s) ? 0 : -1;
        int mn = 333, mx = -1;
        for (auto c : s) {
            mn = min(mn, int(c));
            mx = max(mx, int(c));
        }
        if (s[0] == mn || s[n - 1] == mx) return 1;
        for (int i = 1; i < n - 1; i ++) if (s[i] == mn || s[i] == mx) return 2;
        return 3;
    }
};