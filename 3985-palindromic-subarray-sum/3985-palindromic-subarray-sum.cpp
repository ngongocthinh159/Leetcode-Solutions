struct manacher {
    vector<int> d;
    int n;
    manacher(vector<int> &a) {
        n = a.size();
        vector<int> tmp;
        tmp.push_back(-1);
        for (auto x : a) {
            tmp.push_back(x);
            tmp.push_back(-1);
        }
        d = solve(tmp);
    }
    vector<int> solve(vector<int> &tmp) {
        int n = tmp.size();
        vector<int> d(n);
        for (int i = 0, l = -1, r = -1; i < n; i++) {
            if (i <= r) {
                d[i] = min(r - i + 1, d[r + l - i]);
            }
            while (i + d[i] < n && i - d[i] >= 0 && tmp[i + d[i]] == tmp[i - d[i]]) d[i]++;
            if (i + d[i] - 1 > r) {
                l = i - d[i] + 1;
                r = i + d[i] - 1;
            }
        }
        return vector<int>(d.begin() + 1, prev(d.end()));
    }
    int get_d_odd(int idx) {
        assert(0 <= idx && idx < n);
        return d[2*idx]/2;
    }
    int get_d_even(int idx) {
        assert(0 <= idx && idx < n - 1);
        return d[2*idx + 1]/2;
    }
};
class Solution {
public:
    long long getSum(vector<int>& nums) {
        int n = nums.size();
        vector<long long> pref(n + 1);
        for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + nums[i];
        manacher m(nums);
        long long ans = -1;
        for (int i = 0; i < n; i++) {
            vector<pair<int,int>> v;
            int d_odd = m.get_d_odd(i);
            v.push_back({i - d_odd + 1, i + d_odd - 1});
            if (i + 1 < n) {
                int d_even = m.get_d_even(i);
                v.push_back({i - d_even + 1, i + d_even});
            }
            for (auto [s, e] : v) {
                ans = max(ans, pref[e + 1] - pref[s]);
            }
        }
        return ans;
    }
};