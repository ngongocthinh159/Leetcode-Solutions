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
        
        for (ll i = 0; i < n; i++) {
            if (value[i] <= r) continue;
            ll diff = value[i] - r;
            ll time = (diff + decay[i] - 1)/decay[i];
            value[i] = value[i] - time * decay[i];
        }
        priority_queue<pair<ll,ll>> q;
        for (ll i = 0; i < n; i++) if (value[i] > 0) q.push({value[i], i});
        while (q.size() && oper) {
            auto p = q.top();
            q.pop();

            oper--;
            ans += p.first;
            ans %= MOD;

            int nval = p.first - decay[p.second];
            if (nval > 0)
                q.push({nval, p.second});
        }
        return ans;
    }
};