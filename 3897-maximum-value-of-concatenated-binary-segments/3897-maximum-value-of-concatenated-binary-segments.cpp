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
        vector<array<int,2>> v;
        for (int i = 0; i < n; i++)
            v.push_back({nums1[i], nums0[i]});
        sort(v.begin(), v.end(), [](auto &a, auto &b) {
            int bit[4] = {1,0,1,0};
            int i = 0, j = 0;
            long long c[4] = {a[0], a[1], b[0], b[1]};
            long long d[4] = {b[0], b[1], a[0], a[1]};
            int cnt1 = c[0], cnt2 = d[0];
            while (i < 4 && j < 4) {
                if (cnt1 == 0) {
                    i++;
                    if (i < 4) cnt1 = c[i];
                    continue;
                }
                if (cnt2 == 0) {
                    j++;
                    if (j < 4) cnt2 = d[j];
                    continue;
                }

                if (bit[i] != bit[j]) return bit[i] > bit[j];

                int take = min(cnt1, cnt2);
                cnt1 -= take;
                cnt2 -= take;
            }
            return false;
        });
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