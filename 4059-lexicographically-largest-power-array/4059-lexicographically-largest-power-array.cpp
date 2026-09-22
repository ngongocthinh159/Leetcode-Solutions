class Solution {
public:
    vector<int> largestPower(vector<int>& nums) {
        int n = nums.size();
        int mask = (1 << 15) - 1;
        vector<int> v;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < n; i++) {
            if (nums.back() != mask) {
                for (int j = 0; j < int(nums.size()) - 1; j++) nums[j] = nums[j] & nums.back();
                mask = nums.back();
                v.push_back(nums.back());
                nums.pop_back();
                sort(nums.begin(), nums.end());
            } else {
                v.push_back(nums.back());
                nums.pop_back();
            }
        }
        vector<int> ans(15);
        vector<bool> end(15);
        for (int i = 0; i < n; i++) {
            for (int bit = 0; bit < 15; bit++) if (!((v[i] >> bit) & 1)) {
                end[bit] = 1;
            }
            for (int bit = 0; bit < 15; bit++) if (!end[bit]) ans[14 - bit]++;
        }

        return ans;
    }
};