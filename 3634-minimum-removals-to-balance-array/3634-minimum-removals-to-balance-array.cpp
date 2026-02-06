class Solution {
public:
    int minRemoval(vector<int>& nums, int k) {
        int n = nums.size(), ans = INT_MAX;
        sort(nums.begin(), nums.end());
        for (int r = 0, l = 0; r < n; r++) {
            while (l < r && 1ll * nums[l] * k < nums[r]) l++;
            ans = min(ans, n - (r - l + 1));
        }
        return ans;
    }
};