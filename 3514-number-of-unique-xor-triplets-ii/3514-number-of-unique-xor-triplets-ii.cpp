class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        int msb = -1;
        for (auto x : nums) {
            msb = max(msb, 32 - __builtin_clz(x) - 1);
        }
        int nmask = (1 << (msb + 1));
        vector<bool> ok(nmask);
        vector<bool> vis(nmask);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) ok[nums[i] ^ nums[j]] = 1;
        int ans = 0;
        for (int i = 0; i < nmask; i++)
            for (int j = 0; j < n; j++) if (ok[i ^ nums[j]]) vis[i] = 1;
        for (int i = 0; i < nmask; i++) if (vis[i]) ans++;
        return ans;
    }
};