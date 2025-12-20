class Solution {
public:
    long long cal(int l, int r, vector<long long> &pref, int n) {
        if (l < 0 || r < 0) return 0;
        if (l >= n || r >= n) return 0;
        if (l > r) return 0;
        return pref[r + 1] - pref[l];
    }
    long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
        int n = prices.size();
        vector<long long> pref(n + 1);   
        vector<long long> pref1(n + 1);   
        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + prices[i] * strategy[i];
            pref1[i + 1] = pref1[i] + prices[i];
        }
        long long ans = pref[n];
        for (int i = k - 1; i < n; i++) {
            int r = i, l = i - k + 1, m = i - k/2 + 1;
            ans = max(ans, cal(0, l - 1, pref, n) +
                            cal(m, r, pref1, n) +
                            cal(r + 1, n - 1, pref, n));
        }
        return ans;
    }
};