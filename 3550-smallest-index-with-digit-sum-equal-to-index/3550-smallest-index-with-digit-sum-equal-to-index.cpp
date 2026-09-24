class Solution {
public:
    int smallestIndex(vector<int>& nums) {
        int n = nums.size();
        auto sumDigit = [](int x) -> int {
            int res = 0;
            while (x) {
                res += x % 10;
                x /= 10;
            }
            return res;
        };
        for (int i = 0; i < n; i++) {
            if (sumDigit(nums[i]) == i) return i;
        }
        return -1;
    }
};