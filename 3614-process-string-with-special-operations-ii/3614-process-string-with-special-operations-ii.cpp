class Solution {
public:
    char processStr(string s, long long k) {
        long long len = 0, n = s.size();
        vector<pair<char,int>> v;
        for (int i = 0; i < n; i++) {
            if (s[i] == '*') {
                if (len >= 1) {
                    len--;
                    v.push_back({'*', -1});
                } else {
                    v.push_back({'*', 0});
                }
            } else if (s[i] == '#') {
                len = len * 2;
                v.push_back({'#', 1});
            } else if (s[i] == '%') {
                v.push_back({'%', 1});
            } else {
                v.push_back({'^', s[i]});
                len++;
            }
        }
        // cout << len << '\n';
        // if (k > len - 1) return '.';
        for (int i = int(v.size()) - 1; i >= 0; i--) {
            if (k > len - 1) return '.';
            if (v[i].first == '*') {
                len += -v[i].second;
            } else if (v[i].first == '#') {
                len /= 2;
                k %= len;
            } else if (v[i].first == '%') {
                k = len - 1 - k;
            } else if (v[i].first == '^') {
                if (k == len - 1) return v[i].second;
                len--;
            }
        }
        return '.';
    }
};