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
                for (int j = 30; j >= 0; j--) if (((cmask >> j) & 1) && !((nums[i] >> j) & 1)) {
                    long long tmp = ((1LL << (j + 1)) - 1);
                    cost[i] = (tmp & cmask) - (tmp & nums[i]);
                    break;
                }
            }
            sort(cost.begin(), cost.end());
            for (int i = 0; i < m; i++) tot += cost[i];
            if (tot <= k) {
                mask = cmask;
            }
        }
        return mask;
    }
};