class Solution {
public:
    const int MOD = 1e9 + 7;
    long long expo(long long a, long long b) {
        long long res = 1;
        long long cur = a;
        while (b) {
            if (b & 1) res = res * cur % MOD;
            cur = cur * cur % MOD;
            b >>= 1;
        }
        return res;
    }
    int maxValue(vector<int>& nums1, vector<int>& nums0) {
        int n = nums1.size();
        vector<array<int,2>> start,end,mid,v;
        for (int i = 0; i < n; i++) {
            if (nums1[i] != 0 && nums0[i] == 0) start.push_back({nums1[i], nums0[i]});
            else if (nums1[i] == 0 && nums0[i] != 0) end.push_back({nums1[i], nums0[i]});
            else mid.push_back({nums1[i], nums0[i]});
            // v.push_back({nums1[i], nums0[i]});
        }
        sort(mid.begin(), mid.end(), [](auto &a, auto &b) {
            // if (a[1] == 0 && b[1] != 0) return true;
            if (a[0] > b[0]) return true;
            if (a[0] == b[0] && a[1] < b[1]) return true;
            return false;
        });
        v.insert(v.end(), start.begin(), start.end());
        v.insert(v.end(), mid.begin(), mid.end());
        v.insert(v.end(), end.begin(), end.end());
        // for (auto &vv : v) cout << vv[0] << ' ' << vv[1] << '\n';
        // 2^0 + 2^1 + .. + 2^x = 2^(x + 1) - 1
        auto sumTo = [&] (long long r) -> long long  {
            long long res = expo(2, r + 1);
            res -= 1;
            if (res < 0) res += MOD;
            return res;
        };
        auto range = [&] (long long l, long long r) -> long long {
            long long res = sumTo(r) - (l == 0 ? 0 : sumTo(l - 1));
            if (res < 0) res += MOD;
            return res;
        };
        long long res = 0;
        long long SS = 0;
        for (int i = n - 1; i >= 0; i--) {
            long long start1 = SS + v[i][1];
            long long end1 = start1 + v[i][0] - 1;
            res += range(start1, end1);
            if (res >= MOD) res -= MOD;
            SS += v[i][0] + v[i][1];
        }
        return res;
    }
};