#define ll long long
class Solution {
public:
    bool repeatedStringMatch(string a, string b, int x, int y) {
        int n = a.size(), m = b.size();
        const int LOG = 31;
        vector<vector<pair<ll,ll>>> jump(n + 1, vector<pair<ll,ll>>(LOG)); // stopIdx, aIdx
        for (int start = 0; start < n; ++start) {
            bool match = true;
            int i = start;
            for (int j = 0; j < m; ++j, ++i) {
                if (a[i%n] != b[j]) {
                    match = false;
                    break;
                }
            }
            if (match) jump[start + 1][0] = {i % n + 1, i / n};
        }
        for (int j = 1; j < LOG; ++j) 
            for (int i = 1; i <= n; ++i) {
                ll firstPos = jump[i][j - 1].first;
                ll secondPos = jump[firstPos][j - 1].first;
                ll cnt = jump[i][j - 1].second + jump[firstPos][j - 1].second;
                jump[i][j] = {secondPos, cnt};
            }
        for (int start = 1; start <= n; ++start) {
            ll tot = 0;
            int i = start;
            for (int bit = LOG - 1; bit >= 0; --bit) if ((y >> bit) & 1) {
                tot += jump[i][bit].second;
                i = jump[i][bit].first;
            }
            if (i == 0) continue;
            if (i == 1) tot--;
            ll times = tot + 1;
            if (times <= x) return true;
        }
        return false;
    }
};