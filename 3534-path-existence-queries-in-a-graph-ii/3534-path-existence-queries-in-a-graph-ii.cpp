class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<int> node_at_idx(n), idx_of_node(n);
        iota(node_at_idx.begin(), node_at_idx.end(), 0);
        sort(node_at_idx.begin(), node_at_idx.end(), [&](int i, int j) {
            return nums[i] < nums[j];
        });
        for (int i = 0; i < n; i++) {
            idx_of_node[node_at_idx[i]] = i;
        }
        int msb = 32 - __builtin_clz(n) - 1;
        vector<vector<int>> par(n, vector<int>(msb + 1));
        for (int i = n - 1, l = n - 1; i >= 0; i--) {
            while (nums[node_at_idx[l]] - nums[node_at_idx[i]] > maxDiff)
                l--;
            par[i][0] = l;
        }
        for (int j = 1; j <= msb; j++)
            for (int i = 0; i < n; i++) 
                par[i][j] = par[par[i][j - 1]][j - 1];
        vector<int> ans(queries.size());
        for (int i = 0; i < queries.size(); i++) {
            int u = queries[i][0];
            int v = queries[i][1];
            if (idx_of_node[u] > idx_of_node[v]) swap(u, v);
            int idx_u = idx_of_node[u];
            int idx_v = idx_of_node[v];
            if (idx_u == idx_v) {
                ans[i] = 0;
                continue;
            }
            int jump = 0;
            bool found = false;
            for (int j = msb; j >= 0; j--) {
                if (par[idx_u][j] >= idx_v) {
                    found = true;
                } else {
                    jump += (1 << j);
                    idx_u = par[idx_u][j];
                }
            }
            if (found)
                ans[i] = jump + 1;
            else
                ans[i] = -1;
        }
        return ans;
    }
};