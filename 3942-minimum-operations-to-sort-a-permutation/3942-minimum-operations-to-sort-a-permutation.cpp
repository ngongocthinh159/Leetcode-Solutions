class Solution {
public:
    const int IINF = 1e9;
    int minOperations(vector<int>& nums) {
        if (nums.size() == 1) return 0;
        int ans = cal1(nums);
        ans = min(ans, cal2(nums) + 1);
        reverse(nums.begin(), nums.end());
        ans = min(ans, 1 + cal1(nums));
        ans = min(ans, cal2(nums) + 2);
        return ans >= IINF ? -1 : ans;
    }
    int cal1(vector<int>& nums) {
        int n = nums.size();
        int cnt = 0, idx;
        for (int i = 0; i < n - 1; ++i) if (nums[i] > nums[i + 1]) cnt++, idx = i;
        if (cnt >= 2) return IINF;
        if (cnt == 0) return 0;
        if (nums[0] >= nums[n - 1]) return idx + 1;
        return IINF;
    }
    int cal2(vector<int>& nums) {
        int n = nums.size();
        int cnt = 0, idx;
        for (int i = 0; i < n - 1; ++i) if (nums[i] < nums[i + 1]) cnt++, idx = i;
        if (cnt >= 2) return IINF;
        if (cnt == 0) return 0;
        if (nums[0] <= nums[n - 1]) return idx + 1;
        return IINF;
    }
};