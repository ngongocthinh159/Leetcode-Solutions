class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        if (n == 1) {
            if (nums[0] == target) return 0;
            return -1;
        }
        if (nums[0] < nums[n - 1]) {
            int l = -1, r = n;
            while (r - l > 1) {
                int m = l + (r - l)/2;
                if (nums[m] == target) return m;
                if (nums[m] > target)
                    r = m;
                else
                    l = m;
            }
            return -1;
        }
        int l = -1, r = n;
        while (r - l > 1) {
            int m = l + (r - l)/2;
            if (nums[m] == target) return m;
            if (nums[m] > nums[n - 1]) {
                if (target >= nums[l + 1] && target < nums[m])
                    r = m;
                else
                    l = m;
            } else {
                if (target > nums[m] && target <= nums[r - 1])
                    l = m;
                else
                    r = m;
            }
        }
        return -1;
    }
};