#define N 3005
#define ll long long
ll fact[N], inv[N];
const int MOD = 1e9 + 7;
ll expo(ll a, ll b) {
    ll res = 1, cur = a;
    while (b) { 
        if (b &1) res = res * cur % MOD;
        cur = cur * cur % MOD;
        b>>= 1;
    }
    return res;
}
auto init = [] {
    fact[0] = 1;
    for (int i = 1; i < N; i++) fact[i] = fact[i - 1] * i % MOD;
    inv[N - 1] = expo(fact[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % MOD;
    return 0;
}();
class Solution {
public:
    int makeStringSorted(string s) {
        int n = s.size();
        ll ans = 0;
        int f[26]{};
        for (auto c : s) f[c - 'a']++;
        for (int i = 0; i < n; i++) {
            int tot = 0;
            ll cur = 1, sum = 1;
            for (int c = 0; c < 26; c++) if (f[c]) tot += f[c], cur = cur * inv[f[c]] % MOD;
            cur = cur * fact[tot - 1] % MOD;
            for (int c = 0; c < s[i] - 'a'; c++) if (f[c]) {
                sum = cur * fact[f[c]] % MOD * inv[f[c] - 1] % MOD;
                ans += sum;
                if (ans >= MOD) ans -= MOD;
            }
            f[s[i] - 'a']--;
        }
        return ans;
    }
};