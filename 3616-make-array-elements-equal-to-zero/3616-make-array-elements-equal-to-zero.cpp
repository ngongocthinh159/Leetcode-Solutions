class Solution {
public:
    int countValidSelections(vector<int>& nums) {
        int n = nums.size();
        int tot = 0, cur = 0, ans = 0;
        for (auto x : nums) tot += x;
        for (int i = 0; i < n; i++) {
            cur += nums[i];
            if (nums[i] == 0 && (cur * 2 == tot || cur * 2 + 1 == tot )) ans++;
        }
        cur = 0;
        for (int i = n - 1; i >= 0; i--) {
            cur += nums[i];
            if (nums[i] == 0 && (cur * 2 == tot || cur * 2 + 1 == tot )) ans++;
        }
        return ans;
    }
};