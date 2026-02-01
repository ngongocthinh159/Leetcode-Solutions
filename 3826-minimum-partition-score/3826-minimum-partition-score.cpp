#define ll long long
class Solution {
public:
    int n;
    const ll LINF = 1e18;
    vector<ll> dp, ndp, pref;
    bool minimize(ll &x, ll y) {
        if (x > y) {
            x = y;
            return true;
        }
        return false;
    }
    void dfs(int l, int r, int optl, int optr) {
        if (l > r) return;

        int m = (l + r) / 2, opt;
        ll best = LINF;
        for (int j = optl; j <= min(optr, m); j++) {
            ll sum = pref[m + 1] - pref[j];
            ll cost = sum * (sum + 1) / 2;
            if (minimize(best, (j ? dp[j - 1] : LINF) + cost)) opt = j;
        }

        ndp[m] = best;
        dfs(l, m - 1, optl, opt);
        dfs(m + 1, r, opt, optr);
    }
    long long minPartitionScore(vector<int>& nums, int k) {
        n = nums.size();
        dp.resize(n);
        ndp.resize(n);
        pref.resize(n + 1);
        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + nums[i];
            dp[i] = pref[i + 1] * (pref[i + 1] + 1) / 2;
        }
        for (int i = 2; i <= k; i++) {
            dfs(0, n - 1, 0, n - 1);
            swap(dp, ndp);
        }
        return dp[n - 1];
    }
};