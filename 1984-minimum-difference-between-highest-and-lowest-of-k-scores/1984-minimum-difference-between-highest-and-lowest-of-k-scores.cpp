class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        int n = nums.size(), ans = INT_MAX;
        sort(nums.begin(), nums.end());
        for (int i = k - 1; i < n; i++) {
            ans = min(ans, nums[i] - nums[i - k + 1]);
        }
        return ans;
    }
};