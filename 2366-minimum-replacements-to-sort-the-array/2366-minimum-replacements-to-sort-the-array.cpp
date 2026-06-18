// Go from right to left, we only need to relax a number if it is larger than the next number
// Optimal strategy to relax a number X with cap is Y (next number) so that smallest number is maximize:
// - We always have to divide to k = ceil(X / Y) partition -> this is fixed
// - After have k fixed, we can find smallest = floor(X / k)
#define ll long long
class Solution {
public:
    long long minimumReplacement(vector<int>& nums) {
        int n = nums.size();
        ll oper = 0;
        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] <= nums[i + 1]) continue;
            if (nums[i] % nums[i + 1] == 0) {
                oper += nums[i]/nums[i + 1] - 1;
                nums[i] = nums[i + 1];
                continue;
            }
            oper += nums[i] / nums[i + 1];
            ll k = (nums[i] + nums[i + 1] - 1) / nums[i + 1];
            nums[i] = nums[i] / k;
        }
        return oper;
    }
};