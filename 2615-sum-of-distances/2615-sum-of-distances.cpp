class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int,vector<int>> f;
        for (int i = 0; i < n; i++) f[nums[i]].push_back(i);
        vector<long long> ans(n);
        for (auto &[x, list] : f) {
            long long cur = 0;
            for (int i = 1; i < int(list.size()); i++) cur += list[i] - list[0];
            ans[list[0]] = cur;
            long long left = 0, right = int(list.size()) - 1;
            for (int i = 1; i < int(list.size()); i++) {
                int delta = list[i] - list[i - 1];
                cur -= right * delta;
                cur += (left + 1) * delta;
                ans[list[i]] = cur;
                left++;
                right--;
            }
        }
        return ans;
    }
};