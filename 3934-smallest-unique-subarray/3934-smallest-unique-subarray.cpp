class Solution {
public:
    long long base = 1e6;
    long long MOD = 1e9 + 7;
    vector<long long> basepow;
    bool check(int n, int len, vector<long long> &pref) {
        unordered_map<long long,int> f;
        for (int i = len - 1; i < n; i++) {
            int r = i + 1, l = r - len;
            long long cur = pref[r] - pref[l] * basepow[r - l] % MOD;
            if (cur < 0) cur += MOD;
            f[cur]++;
        }
        for (auto [cur, cnt] : f) if (cnt == 1) return true;
        return false;
    }
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        int l = -1, r = n;
        vector<long long> pref(n + 1);
        basepow.resize(n + 1);
        basepow[0] = 1;
        for (int i = 0; i < n; i++) {
            pref[i + 1] = (pref[i] * base % MOD + nums[i]) % MOD;
            basepow[i + 1] = basepow[i] * base % MOD;
        }
        while (r - l > 1) {
            int m = l + (r - l)/2;
            if (check(n, m, pref))
                r = m;
            else
                l = m;
        }
        return r;
    }
};