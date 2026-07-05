#define N 1000005
int spf[N];
auto init = []{
    for (int i = 2; i < N; i++) spf[i] = i;
    for (int i = 2; i * i < N; i++) if (spf[i] == i) 
        for (int j = i * i; j < N; j += i) spf[j] = min(spf[j], i);
    return false;
}();
class Solution {
public:
    int divisibleGame(vector<int>& nums) {
        int n = nums.size();
        long long mxDif = LLONG_MIN;
        long long mnf = LLONG_MAX;
        vector<long long> pref(n + 1);
        for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + nums[i];
        for (int r = 0; r < n; r++) {
            unordered_map<int,long long> f;
            long long mx = 0, mnFact = LLONG_MAX;
            for (int l = r; l >= 0; l--) {
                int x = nums[l];
                while (x != 1) {
                    int fact = spf[x];
                    while (x % fact == 0) x /= fact;

                    f[fact] += nums[l];
                    long long sum = f[fact];

                    if (mx < sum) {
                        mx = sum;
                        mnFact = fact;
                    } else if (mx == sum) {
                        mnFact = min(mnFact, 1ll * fact);
                    }
                }

                long long dif = mx * 2 - (pref[r + 1] - pref[l]);
                if (mxDif < dif) {
                    mxDif = dif;
                    mnf = mnFact;
                } else if (mxDif == dif) {
                    mnf = min(mnf, mnFact);
                }
            }
        }
        const int MOD = (1e9 + 7);
        if (mnf == LLONG_MAX) mnf = 2;
        if (mxDif < 0) mxDif += MOD;
        return mxDif * mnf % MOD;
    }
};