class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        int n = nums.size();
        int f[32]{};
        for (int i = 0; i < n; ++i) for (int bit = 0; bit <= 30; ++bit) if ((nums[i] >> bit) & 1) f[bit]++;
        const int MOD = 1e9 + 7;
        int ans = 0;
        for (int i = 0; i < k; ++i) {
            int cur = 0;
            for (int bit = 0; bit <= 30; ++bit) if (f[bit]) {
                cur |= (1 << bit);
                f[bit]--;
            }
            ans = (ans + 1ll * cur * cur % MOD) % MOD;
        }
        return ans;
    }
};