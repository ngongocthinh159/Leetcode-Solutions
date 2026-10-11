class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        unordered_map<int,int> f;
        int mx = -1, x, avail;
        long long ans = 0, ops = 0, cnt = 0;
        for (int i = 0; i < n; i++) {
            int diff = abs(nums1[i] - nums2[i]);
            f[diff]++, mx = max(mx, diff);
        }
        for (int i = mx; i >= 0; i--) {
            ops += cnt;
            cnt += f[i];
            if (ops > k1 + k2) break;
            x = i;
            avail = k1 + k2 - ops;
        }
        if (x == 0) return 0;
        for (int i = 0; i < n; i++) {
            int cur = min(abs(nums1[i] - nums2[i]), x);
            if (cur >= x && avail) {
                cur--;
                avail--;
            }
            ans += 1ll * cur * cur;
        }
        return ans;
    }
};