class Solution {
public:
    vector<vector<int>> dp;
    int dfs(int i, int sum, vector<int> &nums) {
        if (sum < 0) return 1e8;
        if (i == nums.size()) {
            if (sum == 0) return 0;
            return 1e8;
        }
        if (dp[i][sum] != -1) return dp[i][sum];

        int res = 1e8;
        int x = nums[i];
        int oper = 0;
        res = min(res, dfs(i + 1, sum, nums));
        while (x) {
            res = min(res, oper + dfs(i + 1, sum - x, nums));
            oper++;
            x >>= 1;
        }
        // res = min(res, oper + dfs(i + 1, sum, nums));

        x = nums[i];
        oper = 0;
        while (x <= sum) {
            res = min(res, oper + dfs(i + 1, sum - x, nums));
            oper++;
            x <<= 1;
        }

        return dp[i][sum] = res;
    }
    int minOperations(vector<int>& nums, int sum) {
        int n = nums.size();
        dp = vector<vector<int>>(n, vector<int>(sum + 1, -1));
        int res = dfs(0, sum, nums);
        if (res >= 1e8) return -1;
        return res;
    }
};