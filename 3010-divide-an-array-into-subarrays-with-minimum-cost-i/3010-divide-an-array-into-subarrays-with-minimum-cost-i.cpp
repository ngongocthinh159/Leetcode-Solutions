class Solution {
public:
    int minimumCost(vector<int>& nums) {
        int mn1 = INT_MAX, mn2 = INT_MAX;
        int n = nums.size();
        for (int i = 1; i < n; i++) {
            if (nums[i] < mn1) {
                mn2 = mn1;
                mn1 = nums[i];
            } else if (nums[i] < mn2) {
                mn2 = nums[i];
            }
        }
        return nums[0] + mn1 + mn2;
    }
};