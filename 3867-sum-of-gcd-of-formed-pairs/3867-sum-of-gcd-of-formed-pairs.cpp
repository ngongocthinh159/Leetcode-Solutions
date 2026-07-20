class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        int n = nums.size();
        vector<int> pref(n);
        int mx = -1;
        for (int i = 0; i < n; i++) {
            mx = max(mx, nums[i]);
            pref[i] = __gcd(nums[i], mx);
        }
        sort(pref.begin(), pref.end());
        long long ans = 0;
        for (int i = 0, j = n - 1; i < j; i++, j--) {
            ans += __gcd(pref[i], pref[j]);
        }
        return ans;
    }
};