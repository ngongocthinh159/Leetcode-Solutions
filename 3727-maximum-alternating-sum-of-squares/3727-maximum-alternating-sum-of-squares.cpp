class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        long long ans = 0;
        vector<int> v(n);
        for (int i = 0; i < n; ++i) v[i] = abs(nums[i]);
        int mid = n - (n + 1)/2;
        nth_element(v.begin(), v.begin() + mid - 1, v.end());
        for (int i = 0; i < mid; ++i) ans -= 1ll * v[i] * v[i];
        for (int i = mid; i < n; ++i) ans += 1ll * v[i] * v[i];
        return ans;
    }
};