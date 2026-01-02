#define ll long long
class Solution {
public:
    bool check(ll target, int n, vector<int> b) {
        ll sum = 0;
        for (auto &x : b) sum += min(1LL * x, target);
        return sum / n >= target;
    }
    long long maxRunTime(int n, vector<int>& batteries) {
        ll l = 1, r = 1e15;
        while (r - l > 1) {
            ll m = l + (r - l)/2;
            if (check(m, n, batteries))
                l = m;
            else
                r = m;
        }
        return l;
    }
};