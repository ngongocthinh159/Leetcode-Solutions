class Solution {
public:
    vector<int> kthRemainingInteger(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(), m = queries.size();
        vector<int> ans(m);
        vector<int> pref(n + 1);
        unordered_set<int> S;
        for (int i = 0; i < n; i++) {
            S.insert(nums[i]);
            pref[i + 1] = pref[i] + (nums[i]%2 == 0);
        }
        auto cnt = [&](int mid, int l, int r) -> int {
            int x = (mid + 1) * 2;
            if (x < nums[l]) return mid + 1;
            if (x > nums[r]) return mid + 1 - (pref[r + 1] - pref[l]);
            auto it = upper_bound(nums.begin(), nums.end(), x);
            it--;
            int idx = it - nums.begin();
            return mid + 1 - (pref[idx + 1] - pref[l]);
        };
        for (int i = 0; i < m; i++) {
            int l = queries[i][0];
            int r = queries[i][1];
            int k = queries[i][2];

            int L = -1, R = 2*(n + k) + 1;
            while (R - L > 1) {
                int mid = L + (R - L)/2;
                int res = cnt(mid, l, r);
                if (res == k) {
                    int x = (mid + 1) * 2;
                    if (nums[l] <= x && x <= nums[r] && S.count(x)) {
                        R = mid;
                    } else {
                        ans[i] = x;
                        break;
                    }
                }
                if (res < k)
                    L = mid;
                else
                    R = mid;
            }
        }
        return ans;
    }
};