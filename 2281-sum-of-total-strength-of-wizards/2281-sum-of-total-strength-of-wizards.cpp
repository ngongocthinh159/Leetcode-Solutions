#define ll long long
class Solution {
public:
    int totalStrength(vector<int>& strength) {
        int n = strength.size();
        const int MOD = 1e9 + 7;
        ll ans = 0;
        vector<long long> pref(n + 1);
        vector<long long> pp(n + 1);
        vector<long long> dp(n);
        vector<array<ll,2>> st;
        for (int i = 0; i < n; i++) {
            pref[i + 1] = (pref[i] + strength[i]) % MOD;
            pp[i + 1] = (pp[i] + pref[i + 1]) % MOD;
            ll sum_min_i = strength[i];
            while (st.size() && strength[st.back()[0]] >= strength[i]) {
                st.pop_back();
            }
            
            ll i_top = st.empty() ? -1 : st.back()[0];
            ll sum_min_top = st.empty() ? 0 : st.back()[1];
            sum_min_i = (sum_min_top + 1ll * (i - i_top) * strength[i] % MOD) % MOD;

            int j = st.empty() ? -1 : st.back()[0];
            ll sum_min_j = st.empty() ? 0 : st.back()[1];
            dp[i] = ((j >= 0 ? dp[j] : 0) + ((pref[i + 1] - pref[j + 1]) % MOD + MOD) % MOD * sum_min_j % MOD) % MOD;
            ll rangeSum = ((i - j) * pref[i + 1] % MOD - ((pp[i] - (j >= 0 ? pp[j] : 0)) % MOD + MOD) % MOD) % MOD;
            if (rangeSum < 0) rangeSum += MOD;
            dp[i] = (dp[i] + rangeSum * strength[i] % MOD) % MOD;
            st.push_back({i, sum_min_i});

            ans = (ans + dp[i]) % MOD;
        }
        return ans;
    }
};