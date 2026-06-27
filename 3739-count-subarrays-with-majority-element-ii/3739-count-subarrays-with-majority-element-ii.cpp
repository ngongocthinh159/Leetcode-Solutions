class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
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