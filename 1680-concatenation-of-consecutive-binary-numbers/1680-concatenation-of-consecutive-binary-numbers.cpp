class Solution {
public:
    const int MOD = 1e9 + 7;
    int concatenatedBinary(int n) {
        long long cur = 0;
        vector<long long> _2pow(31);
        _2pow[0] = 1;
        for (int i = 1; i < 31; i ++) _2pow[i] = _2pow[i - 1] * 2 % MOD;
        for (int i = 1; i <= n; i++) {
            int msb = 32 - __builtin_clz(i) - 1;
            cur = cur * _2pow[msb + 1] % MOD; // 2^(msb + 1) % MOD
            cur += i;
            if (cur >= MOD) cur -= MOD;
        }
        return cur;
    }
};