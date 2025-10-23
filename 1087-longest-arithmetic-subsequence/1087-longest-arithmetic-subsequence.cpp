class Solution {
public:
    int longestArithSeqLength(vector<int>& nums) {
        int n = nums.size();
        vector<int> v = nums;
        for (int i = 0; i < n; i++) v[i] *= -1;
        return max(solve(nums), solve(v));
    }
    int solve(vector<int> &a) {
        int n = a.size();
        int D = 500;
        vector<vector<int>> dp(n, vector<int>(D + 1));
        for (int i = 0; i <= D; i++) dp[n - 1][i] = 1;
        unordered_map<int,int> pos;
        pos[a[n - 1]] = n - 1;
        int ans = 1;
        for (int i = n - 2; i >= 0; i--) {
            for (int j = 0; j <= D; j++) {
                dp[i][j] = 1;
                if (a[i] + j <= D && pos.count(a[i] + j))
                    dp[i][j] = 1 + dp[pos[a[i] + j]][j];
                ans = max(ans, dp[i][j]);
            }
            pos[a[i]] = i;
        }
        return ans;
    }
};