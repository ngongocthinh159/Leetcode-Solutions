class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(3, -1);
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            vector<int> ndp = dp;
            ndp[nums[i] %  3] = max(ndp[nums[i] % 3], nums[i]);
            for (int j = 0; j < 3; j++) if (dp[j] != -1) 
                ndp[(nums[i] + j) % 3] = max(ndp[(nums[i] + j) % 3], dp[j] + nums[i]);
            swap(dp, ndp);
        }
        return dp[0];
    }
};