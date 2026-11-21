class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        int n = nums.size();
        vector<array<int,2>> group;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < n; ) {
            int start = i, cur = nums[i], cnt = 0;
            while (i < n && cur == nums[i]) {
                cnt++;
                i++;
            }
            group.push_back({cur, cnt});
        }
        int m = group.size();
        const int IINF = 1e9;
        vector<vector<int>> dp(m, vector<int>(2, 0));
        
        int ans = 0;
        for (int i = 0; i < m; ++i) {
            dp[i][0] = 1;
            dp[i][1] = group[i][1] == 1 ? 1 : 2;

            if (i >= 1) {
                for (int j = i - 1; j >= i - 2 && j >= 0; --j) {
                    if (group[i][0] - 1 == group[j][0]) {
                        dp[i][0] = max(dp[i][0], dp[j][0] + 1);
                    }
                    if (group[i][0] - 1 == group[j][0] + 1) {
                        dp[i][0] = max(dp[i][0], dp[j][1] + 1);
                    }
                    if (group[i][0] == group[j][0]) {
                        dp[i][1] = max(dp[i][1], dp[j][0] + 1);
                    }
                    if (group[i][0] == group[j][0] + 1) {
                        dp[i][1] = max(dp[i][1], dp[j][1] + 1);
                    }

                    if (group[i][1] != 1) {
                        if (group[i][0] - 1 == group[j][0]) {
                            dp[i][1] = max(dp[i][1], dp[j][0] + 2);
                        }
                        if (group[i][0] - 1 == group[j][0] + 1) {
                            dp[i][1] = max(dp[i][1], dp[j][1] + 2);
                        }
                    }
                }
            }
            ans = max(ans, max(dp[i][0], dp[i][1]));
        }
        return ans;
    }
};