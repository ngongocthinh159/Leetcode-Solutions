class Solution {
public:
    int minSwaps(vector<int>& nums, vector<int>& forbidden) {
        int n = nums.size();
        unordered_map<int,int> f1,f2;
        for (int i = 0; i < n; i++) {
            f1[nums[i]]++;
            f2[forbidden[i]]++;
        }
        for (auto [x, cnt] : f1) if (cnt + f2[x] > n) return -1;
        unordered_map<int,int> f;
        for (int i = 0; i < n; i++) if (nums[i] == forbidden[i]) {
            f[nums[i]]++;
        }
        int ans, mx = 0, sum = 0;
        for (auto &[i, cnt] : f) mx = max(mx, cnt), sum+=cnt;
        if (2*mx >= sum) {
            ans = mx;
        } else {
            ans = sum/2 + (sum&1);
        }
        return ans;
    }
};