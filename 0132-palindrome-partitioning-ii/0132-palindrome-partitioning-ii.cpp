struct manacher {
    int _n;
    vector<int> p;
    manacher(string &s) {
        _n = s.size();
        build(s);
    }
    void build(string &s) {
        string t = "#";
        for (int i = 0;i < s.size();i++) t += s[i], t+= "#";
        auto res = build_p(t);
        p = vector<int>(res.begin() + 1, res.end() - 1);
    }
    vector<int> build_p(string &s) {
        int n = s.size();
        vector<int> d(n);
        for (int i = 0, l = 0, r = 0; i < n; i++) {
            if (i <= r) d[i] = min(r - i + 1, d[r + l - i]);
            while (i - d[i] >= 0 && i + d[i] < n && s[i - d[i]] == s[i + d[i]]) ++ d[i];
            if (i + d[i] - 1 > r) {
                l = i - d[i] + 1;
                r = i + d[i] - 1;
            }
        }
        return d;
    }
    int query_odd(int idx) {
        assert(idx < _n);
        return p[2*idx]/2;
    }
    int query_even(int idx) {
        assert(idx < _n - 1);
        return (p[2*idx + 1] - 1)/2;
    }
};
class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        manacher m(s);
        vector<int> dp(n, INT_MAX);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                int cidx = (i+j)/2;
                int d = (i - j + 1) & 1 ? m.query_odd(cidx) : m.query_even(cidx);
                if (cidx - d + 1 <= j) {
                    int prev = j - 1 < 0 ? 0 : dp[j - 1];
                    dp[i] = min(dp[i], prev + 1);
                }
            }
        }
        return dp[n - 1] - 1;
    }
};