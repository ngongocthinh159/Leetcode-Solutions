class Solution {
public:
    vector<int> maxValue(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return {nums[0]};
        vector<int> dp(n), pref(n), surf(n);
        pref[0] = nums[0];
        for (int i = 1; i < n; i++) pref[i] = max(pref[i - 1], nums[i]);
        surf[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; i--) surf[i] = min(surf[i + 1], nums[i]);
        dp[n - 1] = pref[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            if (pref[i] <= surf[i + 1]) {
                dp[i] = pref[i];
            } else {
                dp[i] = max(nums[i], dp[i + 1]);
            }
        }
        return dp;
    }
};