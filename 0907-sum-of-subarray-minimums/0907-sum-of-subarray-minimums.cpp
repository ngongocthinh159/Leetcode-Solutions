class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        vector<int> st;
        vector<int> dp(n);
        const int MOD = 1e9 + 7;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            while (st.size() && arr[st.back()] >= arr[i]) st.pop_back();
            int j = st.empty() ? -1 : st.back();
            dp[i] = ((j >= 0 ? dp[j] : 0) + 1ll * (i - j) * arr[i] % MOD) % MOD;
            st.push_back(i);

            ans = (ans + dp[i]) % MOD;
        }
        return ans;
    }
};