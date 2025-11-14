class Solution {
public:
    long long minOperations(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int m = nums2.size();
        long long cost = -1, last = nums2[m - 1], ans = 0;
        long long mn = INT_MAX;
        for (int i = 0; i < n; i++) {
            int st = min(nums1[i], nums2[i]);
            int end = max(nums1[i], nums2[i]);
            if (st <= last && last <= end) cost = 0;
            ans += end - st;
            mn = min(mn, min(abs(nums1[i] - last), abs(nums2[i] - last)));
        }
        ans++;
        if (cost == -1)
            ans += mn;
        return ans;
    }
};