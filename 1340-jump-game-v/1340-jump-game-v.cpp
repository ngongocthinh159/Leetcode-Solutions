class Solution {
public:
    int maxJumps(vector<int>& arr, int d) {
        int n = arr.size();
        vector<int> dp(n);
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int i, int j) {
            return arr[i] < arr[j];
        });
        int ans = 0;
        for (int k = 0; k < n; k++) {
            int i = order[k];
            dp[i] = 1;
            for (int j = i + 1; j <= min(i + d, n - 1); j++) {
                if (arr[i] > arr[j]) dp[i] = max(dp[i], 1 + dp[j]);
                else
                    break;
            }
            for (int j = i - 1; j >= max(0, i - d); j--) {
                if (arr[i] > arr[j]) dp[i] = max(dp[i], 1 + dp[j]);
                else
                    break;
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};