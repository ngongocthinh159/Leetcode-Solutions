#define ll long long
class Solution {
public:
    long long minimumReplacement(vector<int>& nums) {
        int n = nums.size();
        ll oper = 0;
        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] <= nums[i + 1]) continue;
            ll w = nums[i] / nums[i + 1];
            ll r = nums[i] % nums[i + 1];
            if (r == 0) {
                nums[i] = nums[i + 1];
                oper += w - 1;
                continue;
            }
            ll L = -1, R = nums[i + 1] + 1;
            while (R - L > 1) {
                ll m = L + (R - L)/2;
                ll totMove = m * w;
                if (r + totMove <= nums[i + 1] - m)
                    L = m;
                else
                    R = m;
            }
            if (r + L * w == nums[i + 1] - L) 
                nums[i] = r + L * w;
            else 
                nums[i] = nums[i + 1] - L - 1;
            oper += w;
        }
        return oper;
    }
};