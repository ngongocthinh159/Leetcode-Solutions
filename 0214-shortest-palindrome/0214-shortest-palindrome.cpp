class Solution {
public:
    vector<int> zfunc(string &s) {
        int n = s.size();
        vector<int> z(n);
        for (int i = 1, l = 0, r = 0; i < n; i++) {
            if (i <= r) z[i] = min(z[i - l], r - i + 1);
            while (i + z[i] < n && s[z[i]] == s[z[i] + i]) z[i]++;
            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }
        return z;
    }
    string shortestPalindrome(string s) {
        int n = s.size();
        string t = s + "#" + string(s.rbegin(), s.rend());
        auto z = zfunc(t);
        int len = 0;
        for (int i = n + 1; i < t.size(); i++) {
            if (i + z[i] == t.size()) {
                len = t.size() - i;
                break;
            }
        }
        string sur = s.substr(len);
        reverse(sur.begin(), sur.end());
        return sur + s;
    }

};