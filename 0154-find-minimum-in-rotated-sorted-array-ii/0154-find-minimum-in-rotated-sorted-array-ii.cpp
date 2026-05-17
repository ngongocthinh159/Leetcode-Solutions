class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();
        int l = -1, r = n - 1;
        while (r - l > 1) {
            int m = l + (r - l)/2;
            if (nums[m] > nums[r]) {
                l = m;
            }
            else if (nums[m] == nums[r]) r--;
            else r = m;
        }
        return nums[r];
    }
};