#define ll long long
#define N 100005
ll inv[N];
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
auto init = []{
    for (int i = 0; i < N; i++) inv[i] = expo(i, MOD - 2);
    return false;
}();
class Solution {
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        const int MAGIC_NUM = sqrt(n);
        unordered_map<int,vector<ll>> f;
        f.reserve(MAGIC_NUM);
        for (auto &q : queries) {
            auto [l, r, k, v] = tie(q[0], q[1], q[2], q[3]);
            if (k > MAGIC_NUM) {
                for (int i = l; i <= r; i += k)
                    nums[i] = 1ll * nums[i] * v % MOD;
            } else {
                if (!f.count(k)) f[k].assign(n, 1);
                f[k][l] = f[k][l] * v % MOD;
                int r2 = l + ((r - l) / k + 1) * k;
                if (r2 < n)
                    f[k][r2] = f[k][r2] * inv[v] % MOD;
            }
        }
        for (auto &[k, affect] : f) {
            for (int i = 0; i < k; i++) {
                ll cur = 1;
                for (int j = i; j < n; j += k) {
                    cur = cur * affect[j] % MOD;
                    nums[j] = nums[j] * cur % MOD;
                }
            }
        }
        int res = 0;
        for (int i = 0; i < n; i++) res ^= nums[i];
        return res;
    }
};