class Solution {
public:
    vector<int> getSneakyNumbers(vector<int>& nums) {
        int n = nums.size();
        vector<int> cnt(n + 1, 0);
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (cnt[nums[i]]) ans.push_back(nums[i]);
            else cnt[nums[i]]++;
        }
        return ans;
    }
};