#define ll long long
class Solution {
public:
    const int MOD = 1e9 + 7;
    int maxTotalValue(vector<int>& value, vector<int>& decay, int oper) {
        ll n = value.size();
        ll ans = 0;
        ll l = -1, r = *max_element(value.begin(), value.end()) + 1;
        ll totOper = 0, totGain = 0;
        while (r - l > 1) {
            ll m = l + (r - l)/2;

            bool ok = true;
            ll curOper = 0;
            ll curGain = 0;
            for (ll i = 0; i < n; i++) {
                if (value[i] <= m) continue;
                ll diff = value[i] - m;
                ll time = (diff + decay[i] - 1) / decay[i];

                curOper += time;
                if (time > 0) {
                    ll start = value[i] - (time - 1) * decay[i];
                    ll end = value[i];

                    curGain += (end + start) * time % MOD * 500000004 % MOD;
                    if (curGain >= MOD) curGain -= MOD;
                }
                if (curOper > oper) {
                    ok = false;
                    break;
                }
            }

            if (ok) {
                totGain = curGain;
                totOper = curOper;
                r = m;
            }
            else
                l = m;
        }
        ans += totGain;
        oper -= totOper;
        
        int mx = INT_MIN, cnt = 0;
        for (ll i = 0; i < n; i++) {
            if (value[i] <= r) continue;
            ll diff = value[i] - r;
            ll time = (diff + decay[i] - 1)/decay[i];
            value[i] = value[i] - time * decay[i];
        }
        for (ll i = 0; i < n; i++) {
            if (mx == value[i]) cnt++;
            else if (mx < value[i]) {
                mx = value[i];
                cnt = 1;
            }
        }
        if (mx > 0) {
            ans += 1ll * min(cnt, oper) * mx % MOD;
            ans %= MOD;
        }
        return ans;
    }
};