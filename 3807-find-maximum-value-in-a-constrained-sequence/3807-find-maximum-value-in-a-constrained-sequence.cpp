class Solution {
public:
    int findMaxVal(int n, vector<vector<int>>& restrictions, vector<int>& diff) {
        int m = restrictions.size();
        vector<int> re(n, INT_MAX);
        for (auto &r : restrictions) re[r[0]] = r[1];
        int nre = INT_MAX;
        for (int i = n - 1; i >= 0; i--) {
            re[i] = min(re[i], nre);
            if (re[i] != INT_MAX && i > 0) {
                nre = re[i] + diff[i - 1];
            }
        }
        int ans = 0, prev = 0;
        for (int i = 1; i < n; i++) {
            int cur = min(re[i], prev + diff[i - 1]);
            ans = max(ans, cur);
            prev = cur;
        }
        return ans;
    }
};