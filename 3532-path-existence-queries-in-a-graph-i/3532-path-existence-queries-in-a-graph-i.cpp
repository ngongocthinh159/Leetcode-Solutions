class Solution {
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        const int LOG = 18;
        vector<int> id(n);
        int cid = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (i != n - 1 && nums[i + 1] - nums[i] > maxDiff) cid++;
            id[i] = cid;
        }
        int m = queries.size();
        vector<bool> ans(m); 
        for (int i = 0; i < m; i++) {
            int u = queries[i][0];
            int v = queries[i][1];
            if (u > v) swap(u, v);
            ans[i] = id[u] == id[v];
        }
        return ans;
    }
};