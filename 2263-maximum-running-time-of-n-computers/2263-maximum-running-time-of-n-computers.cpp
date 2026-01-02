#define ll long long
class Solution {
public:
    bool check(ll target, int n, vector<int> b) {
        for (int i = 1; i <= n; i++) {
            ll sum = 0, last = 0;
            while (sum < target && b.size()) {
                last = b.back();
                sum += b.back();
                b.pop_back();
            }
            if (sum < target) return false;
            ll remain = sum - target;
            ll canUse = sum - last;
            ll willUse = min(remain, canUse);
            if (willUse) b.push_back(willUse);
        }
        return true;
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