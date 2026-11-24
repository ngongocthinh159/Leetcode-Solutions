#define N 15
class Solution {
public:
    int maxLength(vector<int>& nums) {
        int cnt0[N]{};
        int cnt1[N]{};
        int n = nums.size();
        int three = 0, ans = 0;
        vector<int> v = {2,3,5,7,11,13};
        auto add = [&](int x, int delta) {
            for (auto y : v) {
                if (x % y == 0) {
                    cnt1[y] += delta;
                } else {
                    cnt0[y] += delta;
                }
            }
        };
        auto ok = [&]() -> bool {
            for (auto y : v) if (cnt1[y] >= 3 || (cnt1[y] >= 2 && cnt0[y] >= 1)) return false;
            return true;
        };
        for (int i = 0, l = 0; i < n; ++i) {
            add(nums[i], 1);

            while (l <= i && !ok()) add(nums[l++], -1);

            ans = max(ans, i - l + 1);
        }
        return ans;
    }
};