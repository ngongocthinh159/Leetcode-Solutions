class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        int p = 0, k = n - 1;
        for (int i = 0; i <= k;) {
            if (nums[i] == 1 || i < p) {
                i++;
                continue;
            }
            if (nums[i] == 0) {
                swap(nums[p++], nums[i]);
            } else if (nums[i] == 2) {
                swap(nums[k--], nums[i]);
            }
        }
    }
};