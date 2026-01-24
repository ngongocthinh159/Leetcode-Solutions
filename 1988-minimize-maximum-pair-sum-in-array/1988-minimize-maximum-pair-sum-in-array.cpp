class Solution {
public:
    int minPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int ans = INT_MIN, n = nums.size();
        for (int i = 0, j = n - 1; i < j; i++, j--) ans = max(ans, nums[i] + nums[j]);
        return ans;
    }
};