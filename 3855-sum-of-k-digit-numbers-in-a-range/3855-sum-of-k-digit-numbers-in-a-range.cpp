#define ll long long
class Solution {
public:
    const int MOD = 1e9 + 7;
    ll expo(ll a, ll b) {
        ll res = 1;
        ll cur = a;
        while (b) {
            if (b&1) res = res * cur % MOD;
            cur = cur * cur % MOD;
            b >>= 1;
        }
        return res;
    }
    int sumOfNumbers(int l, int r, int k) {
        ll sum = (r + l) * ((r - l) + 1) / 2;
        // u1 * (q^n - 1) / (q - 1)
        sum = sum * expo(r - l + 1, k - 1) % MOD;
        ll tmp = 1 * ((expo(10, k) - 1) + MOD) % MOD * expo(10 - 1, MOD - 2) % MOD;
        return sum * tmp % MOD;
    }
};