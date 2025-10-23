class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        vector<int> pref(n + 1);
        unordered_map<int,int> f;
        f[0] = 0;
        int sum = 0;
        vector<int> dp(n + 1, INT_MAX);
        vector<int> mn(n + 1, INT_MAX);
        int ans = INT_MAX;
        for (int i = 0; i < n; i++) {
            sum += arr[i];

            int val = sum - target;

            if (f.count(val)) {
                dp[i + 1] = i + 1 - f[val];
                if (mn[f[val]] != INT_MAX) {
                    ans = min(ans, dp[i + 1] + mn[f[val]]);
                }
            }
            mn[i + 1] = min(mn[i], dp[i + 1]);

            f[sum] = i + 1;
        }
        return ans == INT_MAX ? -1 : ans;
    }
};