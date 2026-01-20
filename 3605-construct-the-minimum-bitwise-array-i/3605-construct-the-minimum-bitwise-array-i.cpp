class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            if (!(nums[i]&1)) ans[i] = -1;
            else {
                int len = __builtin_ctz(nums[i] + 1);
                ans[i] = nums[i] ^ (1 << (len - 1));
            }
        }
        return ans;
    }
};