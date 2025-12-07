class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        unordered_map<int,int> pos;
        int n = nums.size();
        int S = 0;
        for (auto x : nums) S += x, S%=p;
        if (S == 0) return 0;
        int sum = 0, ans = INT_MAX;
        pos[0] = -1;
        for (int i = 0; i< n; i++) {
            sum += nums[i];
            sum %= p;
            int tar = ((sum - S) % p + p) % p;
            if (pos.count(tar)) {
                ans = min(ans, i - pos[tar]);
            }
            pos[sum] = i;
        }
        if (ans == n) return -1;
        return ans == INT_MAX ? -1 : ans;
    }
};