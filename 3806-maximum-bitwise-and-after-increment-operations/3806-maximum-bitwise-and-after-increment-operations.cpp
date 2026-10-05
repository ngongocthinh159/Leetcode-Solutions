class Solution {
public:
    int maximumAND(vector<int>& nums, int k, int m) {
        int n = nums.size();
        if (m > n) return 0;
        int mask = 0;
        vector<long long> cost(n);
        for (int bit = 30; bit >= 0; bit--) {
            int cmask = mask | (1 << bit);
            long long tot = 0;
            for (int i = 0; i < n; i++) {
                cost[i] = 0;
                if ((cmask & (~nums[i])))  {
                    int msb = 32 - __builtin_clz(cmask & (~nums[i])) - 1;
                    long long tmp = ((1LL << (msb + 1)) - 1);
                    cost[i] = (tmp & cmask) - (tmp & nums[i]);
                }
            }
            nth_element(cost.begin(), cost.begin() + (m - 1), cost.end());
            for (int i = 0; i < m; i++) tot += cost[i];
            if (tot <= k) {
                mask = cmask;
            }
        }
        return mask;
    }
};