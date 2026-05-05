class Solution {
public:
    vector<int> minCost(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> pref(n + 1);
        vector<int> pref2(n + 1);
        for (int i = 0; i < n - 1; i++) {
            if (i == 0 || (abs(nums[i + 1] - nums[i]) < abs(nums[i - 1] - nums[i]))) {
                pref[i] = (i - 1 >= 0 ? pref[i - 1] : 0) + 1;
            } else {
                pref[i] = (i - 1 >= 0 ? pref[i - 1] : 0) + abs(nums[i + 1] - nums[i]); 
            }
        }
        for (int i = n - 1; i >= 1; i--) {
            if (i == n - 1 || (abs(nums[i] - nums[i - 1]) <= abs(nums[i] - nums[i + 1]))) {
                pref2[i] = (i + 1 < n ? pref2[i + 1] : 0) + 1;
            } else {
                pref2[i] = (i + 1 < n ? pref2[i + 1] : 0) + abs(nums[i - 1] - nums[i]);
            }
        }
        int m = queries.size();
        vector<int> ans(m);
        for (int i = 0; i < m; i++) {
            int l = queries[i][0];
            int r = queries[i][1];
            if (l == r) {
                ans[i] = 0;
            } else if (l < r) {
                r--;
                ans[i] = pref[r] - (l - 1 >= 0 ? pref[l - 1] : 0);
            } else {
                r++;
                ans[i] = pref2[r] - (l + 1 < n ? pref2[l + 1] : 0);
            }
        }
        return ans;
    }
};