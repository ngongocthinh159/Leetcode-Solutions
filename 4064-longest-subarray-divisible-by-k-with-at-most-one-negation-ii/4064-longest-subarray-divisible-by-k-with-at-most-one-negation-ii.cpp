class Solution {
public:
    int longestSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>> list(k);
        vector<int> pIdx(k, -2);
        vector<int> sIdx(k, -2);
        pIdx[0] = -1;
        sIdx[0] = n;
        int sum = 0;
        for (int i = 0; i < n; i++) {
            nums[i] %= k;
            if (nums[i] < 0) nums[i] += k;
            list[nums[i]].push_back(i);

            sum += nums[i];
            sum %= k;
            if (pIdx[sum] == -2) pIdx[sum] = i;
        }
        sum = 0;
        for (int i = n - 1; i >= 0; i--) {
            sum += nums[i];
            sum %= k;
            if (sIdx[sum] == -2) sIdx[sum] = i;
        }
        int ans = 0;
        for (int i = 0; i < k; i++) if (list[i].size()) {
            int delta = -2 * i % k;
            if (delta < 0) delta += k;

            for (int p = 0; p < k; p++) if (pIdx[p] != -2) {
                int s = (sum - p + delta) % k;
                if (s < 0) s += k;
                if (sIdx[s] != -2) {
                    int start = pIdx[p] + 1, end = sIdx[s] - 1;
                    auto it = lower_bound(list[i].begin(), list[i].end(), start);
                    if (it != list[i].end() && *it <= end) {
                        ans = max(ans, end - start + 1);
                    }
                }
            }
        }
        unordered_map<int,int> idx;
        idx[0] = -1;
        sum = 0;
        for (int i = 0; i < n; i++) {
            sum += nums[i];
            sum %= k;

            if (idx.count(sum))
                ans = max(ans, i - idx[sum]);
            else 
                idx[sum] = i;
        }
        return ans;
    }
};