#define ll long long
class Solution {
public:
    bool check(ll x, vector<ll> &s, int R, long long k) {
        int n = s.size();
        ll cur = 0;
        vector<ll> effect(n + 1);
        for (int i = 0; i < n; i++) {
            cur += effect[i];
            ll will = max(0LL, x - (s[i] + cur));
            k -= will;
            cur += will;
            effect[min(n, i + 2*R + 1)] -= will;
            if (k < 0)
                return false;
        }
        return true;
    } 
    long long maxPower(vector<int>& stations, int R, int k) {
        int n = stations.size();
        vector<ll> v(n + 1);
        for (int i = 0; i < stations.size(); i++) {
            int st = max(0, i - R);
            int end = min(n, i + R + 1);
            v[st] += stations[i];
            v[end] -= stations[i];
        }
        v.pop_back();
        for (int i = 1; i < n; i++) v[i] += v[i - 1];
        ll l = -1, r = 1e18 + 5;
        while (r - l > 1) {
            ll m = l + (r - l)/2;
            if (check(m, v, R, k))
                l = m;
            else
                r = m;
        }
        return l;
    }
};