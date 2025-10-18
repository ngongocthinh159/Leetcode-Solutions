class Solution {
public:
    int maxDistinctElements(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int prev = INT_MIN, unique = 0;
        for (int i = 0; i < n; i++) {
            int st = max(nums[i] - k, prev + 1);
            if (st <= nums[i] + k) {
                prev = st;
                unique++;
            }
        }
        return unique;
    }
};