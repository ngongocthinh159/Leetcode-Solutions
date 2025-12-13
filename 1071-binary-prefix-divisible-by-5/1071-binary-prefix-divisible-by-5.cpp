class Solution {
public:
    vector<bool> prefixesDivBy5(vector<int>& nums) {
        int re = 0, n = nums.size();
        vector<bool> ans(n);
        for (int i = 0; i < n; i++) {
            re = (2 * re % 5 + nums[i]) % 5;
            ans[i] = re == 0;
        }
        return ans;
    }
};