int cnt[205];
class Solution {
public:
    bool isGood(vector<int>& nums) {
        int n = nums.size(); 
        n--;
        for (int i = 1; i < n; i++) cnt[i] = 1;
        cnt[n] = 2;
        for (int i = 0; i < n + 1; i++){
            if (1 <= nums[i] && nums[i] <= n) cnt[nums[i]]--;
            else return false;
        }
        for (int i = 1; i <= n; i++) if (cnt[i] != 0) return false;
        return true;
    }
};