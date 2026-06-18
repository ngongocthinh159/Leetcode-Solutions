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
            nums[i] = nums[i] / ((nums[i] + nums[i + 1] - 1) / nums[i + 1]);
        }
        return oper;
    }
};