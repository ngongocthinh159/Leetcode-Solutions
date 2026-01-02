class Solution {
public:
    int repeatedNTimes(vector<int>& nums) {
        int cur = -1, cnt = 0;
        for (auto x : nums) {
            if (cnt == 0) {
                cur = x, cnt++;
                continue;
            }
            if (x == cur) return x;
            cnt--;
        }
        sort(nums.begin(), nums.begin() + 4);
        for (int i = 1; i < 4; i++) if (nums[i] == nums[i - 1]) return nums[i];
        return -1;
    }
};