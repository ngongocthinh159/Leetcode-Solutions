class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        long long ans = 0;
        vector<int> v(n);
        for (int i = 0; i < n; ++i) v[i] = abs(nums[i]);
        sort(v.begin(), v.end(), greater<int>());
        for (int i = 0; i < (n + 1)/2; ++i) ans += 1ll * v[i] * v[i];
        for (int i = (n + 1)/2; i < n; ++i) ans -= 1ll * v[i] * v[i];
        return ans;
    }
};