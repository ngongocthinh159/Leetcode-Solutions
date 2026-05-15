class Solution {
public:
    long long minArraySum(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int,vector<int>> f;
        for (int i = 0; i < n; i++) f[nums[i]].push_back(i);
        vector<int> v = nums;
        unordered_set<int> S;
        for (int i = 0; i < n; i++) {
            if (S.count(nums[i])) continue;
            S.insert(nums[i]);
            for (int j = nums[i]; j <= 1e5; j += nums[i]) {
                if (f.count(j)) {
                    for (auto idx : f[j]) v[idx] = min(v[idx], nums[i]);
                }
            }
        }
        long long ans = 0;
        for (auto x : v) ans += x;
        return ans;
    }
};