class Solution {
public:
    int longestAlternating(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> surf(n + 2, vector<int>(2));
        for (int i = n - 1; i >= 0; i--) {
            if (i == n - 1) surf[i + 1][0] = surf[i + 1][1] = 1;
            else {
                surf[i + 1][1] = 1 + (nums[i] < nums[i + 1] ? surf[i + 2][0] : 0);
                surf[i + 1][0] = 1 + (nums[i] > nums[i + 1] ? surf[i + 2][1] : 0);
            }
        }
        int p0 = 0, p1 = 0, ans = 1;
        for (int i = 0; i < n; i++) {
            int np0, np1;
            if (i == 0) np0 = np1 = 1;
            else {
                np1 = 1 + (nums[i] < nums[i - 1] ? p0 : 0);
                np0 = 1 + (nums[i] > nums[i - 1] ? p1 : 0);
            }

            ans = max(ans, max(np0, np1));
            if (i - 1 >= 0 && i + 1 < n && nums[i - 1] != nums[i + 1]) {
                if (nums[i + 1] > nums[i - 1]) ans = max(ans, p1 + surf[i + 2][0]);
                else ans = max(ans, p0 + surf[i + 2][1]);
            }

            p0 = np0;
            p1 = np1;
        }
        return ans;
    }
};