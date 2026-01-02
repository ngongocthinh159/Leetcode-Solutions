#define ll long long
class Solution {
public:
    long long maxRunTime(int n, vector<int>& batteries) {
        ll l = 1, r = 1e15;
        while (r - l > 1) {
            ll m = l + (r - l)/2;
            // for a target, a batteries can be used at most target (the remaining is forced to ignore)
            // if follow this strategy, in the final we can assign more than n computer -> the current target can be archieved
            ll sum = 0;
            for (auto &x : batteries) sum += min(m, 1ll * x);
            if (sum/n >= m)
                l = m;
            else
                r = m;
        }
        return l;
    }
};