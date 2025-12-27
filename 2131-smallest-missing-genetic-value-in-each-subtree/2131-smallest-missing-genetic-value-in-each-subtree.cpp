class Solution {
public:
    vector<vector<int>> g;
    vector<int> ans;
    vector<int> mn;
    int n;
    vector<int> smallestMissingValueSubtree(vector<int>& parents, vector<int>& nums) {
        n = parents.size();
        g.resize(n);
        ans.resize(n);
        mn.resize(n);
        for (int i = 1; i < n; i++) g[parents[i]].push_back(i);
        int mx = n + 1;
        vector<bool> ok(n + 1);
        for (auto x : nums) if (x <= n) ok[x] = 1;
        for (int i = 1; i <= n; i++) if (!ok[i]) {
            mx = i;
            break;
        }
        dfs0(0, nums);
        dfs(0, mx, nums);
        return ans;
    }
    void dfs0(int u, vector<int> &nums) {
        mn[u] = nums[u];
        for (auto v : g[u]) {
            dfs0(v, nums);
            mn[u] = min(mn[v], mn[u]);
        }
    }
    void dfs(int u, int x, vector<int> &nums) {
        ans[u] = x;
        int sz = g[u].size();
        vector<int> pref(sz + 1); 
        vector<int> surf(sz + 2); 
        pref[0] = surf[sz + 1] = INT_MAX;
        for (int i = 0; i < sz; i++)
            pref[i + 1] = min(pref[i], mn[g[u][i]]);
        for (int i = sz - 1; i >= 0; i--)
            surf[i + 1] = min(surf[i + 2], mn[g[u][i]]);
        for (int i = 0; i < sz; i++) {
            int nxt_x = min(x, min(nums[u], min(pref[i], surf[i + 2])));
            dfs(g[u][i], nxt_x, nums);
        }
    }
};