class Solution {
public:
    long long getDescentPeriods(vector<int>& prices) {
        int n = prices.size(), i = 0;
        long long ans = 0;
        while (i < n) {
            int s = i;
            while (i + 1 < n && prices[i + 1] + 1 == prices[i]) i++;
            int len = i - s + 1;
            ans += 1ll * len * (len + 1) / 2;
            i++;
        }
        return ans;
    }
};