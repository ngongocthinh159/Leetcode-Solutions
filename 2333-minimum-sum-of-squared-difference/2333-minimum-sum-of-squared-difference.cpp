class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        vector<int> v(n);
        int mx = -1;
        for (int i = 0; i < n; i++) v[i] = abs(nums1[i] - nums2[i]), mx = max(mx, v[i]);
        int l = -1, r = mx + 1;
        long long ans = 0;
        int used = 0;
        while (r - l > 1) {
            int m = l + (r - l)/2;
            long long tot = 0;
            for (int i = 0; i < n; i++) tot += max(0, v[i] - m);
            if (tot <= k1 + k2) {
                r = m;
                used = tot;
            }
            else
                l = m;
        }
        if (r == 0) return 0;
        int avail = k1 + k2 - used;
        for (int i = 0; i < n; i++) {
            v[i] = min(v[i], r);
            if (v[i] >= r && avail) {
                v[i] -= 1;
                avail--;
            }
            ans += 1ll * v[i] * v[i];
        }
        return ans;
    }
};