#define ll long long
class Solution {
public:
    int totalStrength(vector<int>& strength) {
        int n = strength.size();
        ll ans = 0, tot = 0;
        const int MOD = 1e9 + 7;
        vector<array<ll, 3>> st;
        vector<long long> pref(n);
        for (int i = 0; i < n; i++) {
            pref[i] += ((i > 0 ? pref[i - 1] : 0) + strength[i]) % MOD;
            pref[i] %= MOD;
            ll d = strength[i];
            ll len_sum_d = (st.size() ? st.back()[1] : 0) + d;
            ll suf_sum_d = d;
            bool atLeast = false;
            while (st.size() && strength[st.back()[0]] >= strength[i]) {
                auto vc = st.back();
                st.pop_back();
                int i_c = vc[0];
                ll c = strength[vc[0]];
                ll len_sum_c = vc[1];
                ll suf_sum_c = vc[2];
                atLeast = true;

                ll len_sum_top = st.empty() ? 0 : st.back()[1];
                int i_top = st.empty() ? -1 : st.back()[0];

                ll tmp = (pref[i] - pref[i_c]) % MOD;
                if (tmp < 0) tmp += MOD;
                suf_sum_d += (suf_sum_c + 1ll * (i_c - i_top) * tmp % MOD) % MOD;
                tot -= (suf_sum_c + 1ll * (i_c - i_top) * ((pref[i - 1] - pref[i_c]) % MOD + MOD) % MOD ) * c % MOD;
                tot %= MOD;
                if (tot < 0) tot += MOD;
                len_sum_d = (len_sum_top + 1ll * (i - i_top) * d % MOD) % MOD;
            }
            if (atLeast) {
                ll len_sum_top = st.empty() ? 0 : st.back()[1];
                tot += (len_sum_top + suf_sum_d) * d % MOD;
            }

            if (!atLeast) {
                tot += len_sum_d * d % MOD;
                tot %= MOD;
            }
            st.push_back({i, len_sum_d, suf_sum_d});
            ans += tot;
            ans %= MOD;
        }
        return ans;
    }
};