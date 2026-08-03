class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 1;
        if (n == 2) return 2;
        int msb = -1, cnt = 0;
        for (int i = 0; i < n; i++) {
            int cmsb = 32 - __builtin_clz(nums[i]) - 1;
            if (msb < cmsb) {
                msb = cmsb;
                cnt = 1;
            } else if (msb == cmsb) {
                cnt++;
            }
        }
        return (1ll << (1 + msb)) - 1 + 1;
    }
};