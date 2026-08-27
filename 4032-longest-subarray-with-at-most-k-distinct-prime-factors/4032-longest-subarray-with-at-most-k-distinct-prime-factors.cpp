#define N 100005
int spf[N];
auto init = []{
    for (int i = 2; i < N; i++) spf[i] = i;
    for (int i = 2; i * i < N; i++) if (spf[i] == i)
        for (int j = i * i; j < N; j += i) spf[j] = min(i, spf[j]);

    return 0;
}();
int buf[N];
class Solution {
public:
    vector<int> factorize(int x) {
        vector<int> res;
        while (x != 1) {
            int fact = spf[x];
            while (x % fact == 0) x /= fact;
            res.push_back(fact);
        }
        return res;
    }
    int longestSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>> v(n);
        for (int i = 0; i < n; i++) v[i] = factorize(nums[i]);
        int l = 0, r = n + 1;
        while (r - l > 1) {
            int m = l + (r - l)/2;
            bool ok = false;
            int cnt = 0;
            for (int i = 0; i < m; i++) {
                for (auto x : v[i]) {
                    if (++buf[x] == 1) cnt++;
                }
            }
            if (cnt <= k) ok = true;
            if (!ok) {
                for (int i = m; i < n; i++) {
                    for (auto x : v[i]) if (++buf[x] == 1) cnt++;
                    for (auto x : v[i - m]) if (--buf[x] == 0) cnt--;
                    if (cnt <= k) {
                        ok = true;
                        for (int j = i - m + 1; j <= i; j++) for (auto x : v[j]) buf[x] = 0;
                        break;
                    }
                }
                for (int i = n - m; i < n; i++)
                    for (auto x : v[i]) buf[x] = 0;
            } else {
                for (int i = 0; i < m; i++)
                    for (auto x : v[i]) buf[x] = 0;
            }
            if (ok)
                l = m;
            else
                r = m;
        }
        return l;
    }
};