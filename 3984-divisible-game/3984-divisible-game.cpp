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
        int mxNum = *max_element(nums.begin(), nums.end());
        for (int i = 2; i <= mxNum; i++) if (spf[i] == i) {
            long long cur = 0;
            long long mxSum = LLONG_MIN;
            for (auto &x : nums) {
                if (!(x % i == 0)) x *= -1;
                cur = max(1ll * x, cur + x);
                mxSum = max(cur, mxSum);
            }
            for (auto &x : nums) if (x < 0) x *= -1;
            if (mxDif < mxSum) {
                mxDif = mxSum;
                mnf = i;
            }
        }
        const int MOD = (1e9 + 7);
        if (mxDif == LLONG_MIN) {
            return (-2 + MOD);
        }
        return mxDif * mnf % MOD;
    }
};