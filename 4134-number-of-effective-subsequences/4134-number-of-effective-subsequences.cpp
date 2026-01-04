#define ll long long
#define N 100005
#define BIT 20
int cnt[1 << BIT], _2pow[N];
const int MOD = 1e9 + 7;
auto init = []{
    _2pow[0] = 1;
    for (int i = 1; i < N; i++) _2pow[i] = _2pow[i - 1] * 2ll % MOD;
    return 0;
}();
class Solution {
public:
    const int MOD = 1e9 + 7;
    void clear(int msb) {
        msb++;
        for (int mask = 0; mask < (1 << msb); mask++) cnt[mask] = 0;
    }
    int countEffective(vector<int>& nums) {
        int n = nums.size();
        int mx = *max_element(nums.begin(), nums.end());
        int msb = 32 - __builtin_clz(mx) - 1;
        int tot_or = 0;
        clear(msb);

        int fmask = (1 << (msb + 1)) - 1;
        for (auto x : nums) cnt[x]++, tot_or |= x;
        for (int i = 0; i <= msb; i++)
            for (int mask = fmask; mask >= 0; mask--) if ((mask >> i) & 1) cnt[mask] += cnt[mask ^ (1 << i)];
        int ans = 0;
        for (int mask = 1; mask <= fmask; mask++) if ((tot_or | mask) == tot_or) {
            int cur = _2pow[cnt[tot_or ^ mask]];
            if (__builtin_popcount(mask)&1) {
                ans += cur;
                if (ans >= MOD) ans -= MOD;
            } else {
                ans -= cur;
                if (ans < 0) ans += MOD;
            }
        }
        return ans;
    }
};