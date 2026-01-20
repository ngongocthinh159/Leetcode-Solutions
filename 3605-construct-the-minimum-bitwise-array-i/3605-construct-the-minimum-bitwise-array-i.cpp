class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            if (!(nums[i]&1)) ans[i] = -1;
            else {
                int u = ~nums[i];
                ans[i] = ((u & -u) >> 1) ^ nums[i];
            }
        }
        return ans;
    }
};