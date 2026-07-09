class Solution {
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        const int LOG = 18;
        vector<vector<int>> jump(LOG, vector<int>(n));
        for (int i = n - 1, j = n - 1; i >= 0; i--) {
            while (j >= 0 && nums[j] - nums[i] > maxDiff) j--;
            jump[0][i] = j;
        }
        for (int j = 1; j < LOG; j++)
            for (int i = 0; i < n; i++) jump[j][i] = jump[j - 1][jump[j - 1][i]];
        int m = queries.size();
        vector<bool> ans(m);
        int i = 0;
        for (auto &q : queries) {
            int u = q[0];
            int v = q[1];
            if (u > v) swap(u, v);
            if (jump[LOG - 1][u] < v) ans[i] = false;
            else ans[i] = true;
            i++;
        }
        return ans;
    }
};