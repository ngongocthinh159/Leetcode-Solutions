class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        // f[target_i] - f[target_j] > (i - j) / 2
        // 2 * f[i] - 2 * f[j] > (i - j)
        // 2 * f[i] - i > 2 * f[j] - j 
        // -> 2 * f[j] - j <= 2 * f[i] - i - 1
        int n = nums.size();
        unordered_map<int,int> f;
        f[0]++;
        int cur = 0;
        long long smaller = 0, ans = 0;
        for (int i = 0; i < n; i++) {
            int ncur = cur + (nums[i] == target ? 1 : -1);
            if (ncur > cur) {
                smaller += f[cur];
            } else {
                smaller -= f[ncur];
            }
            cur = ncur;
            f[cur]++;
            ans += smaller;
        }
        return ans;
    }
};