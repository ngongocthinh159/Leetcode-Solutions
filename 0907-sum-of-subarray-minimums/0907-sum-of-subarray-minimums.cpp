class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        vector<int> st;
        vector<long long> res(n, 1);
        for (int i = n - 1; i >= 0; i--) {
            while (st.size() && arr[i] < arr[st.back()]) {
                int idx = st.back();
                res[idx] = res[idx] * (idx - i);
                st.pop_back();
            }
            int idx = st.empty() ? n : st.back();
            res[i] = res[i] * (idx - i);
            st.push_back(i);
        }
        while (st.size()) {
            int idx = st.back();
            res[idx] = res[idx] * (idx + 1);
            st.pop_back();
        }
        const int MOD = 1e9 + 7;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += res[i] * arr[i] % MOD;
            ans %= MOD;
        }
        return ans;
    }
};