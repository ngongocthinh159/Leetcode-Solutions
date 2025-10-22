#define N 100005
int f[N];
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        int mn = INT_MAX, mx = INT_MIN;
        for (auto x : nums) {
            mn = min(mn, x);
            mx = max(mx, x);
            f[x]++;
        }
        int n = nums.size();
        {
            int i = 0;
            for (int j = mn; j <= mx; j++)
                for (int c = 0; c < f[j]; c++) nums[i++] = j;
        }
        int ans = 0;
        for (int i = mn, l = 0, r = 0; i <= mx; i++) {
            while (r < n && nums[r] <= i + k) r++;
            while (nums[l] < i - k) l++;
            ans = max(ans, min(r - l, numOperations + f[i]));
        }
        for (auto x : nums) f[x]--;
        return ans;
    }
};