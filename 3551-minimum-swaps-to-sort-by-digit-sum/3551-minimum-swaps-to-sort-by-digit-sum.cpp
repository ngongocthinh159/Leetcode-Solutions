class Solution {
public:
    vector<bool> vis;
    vector<vector<int>> g;
    int minSwaps(vector<int>& nums) {
        int n = nums.size(), cycle = 0;
        vector<int> v = nums;
        vis.resize(n);
        g.resize(n);
        sort(v.begin(), v.end(), [](int A, int B) {
            int a = A, b = B;
            int x = 0, y = 0;
            while (a) x += a % 10, a /= 10;
            while (b) y += b % 10, b /= 10;
            return (x < y) || (x == y && A < B);
        });
        // for (auto x : v) cout << x << ' ';
        // cout << '\n';
        unordered_map<int,int> toIdx;
        for (int i = 0; i < n; i++) toIdx[v[i]] = i;
        for (int i = 0; i < n; i++) nums[i] = toIdx[nums[i]];
        for (int i = 0; i < n; i++) g[nums[i]].push_back(i);
        for (int i = 0; i < n; i++) if (!vis[i]) {
            dfs(i);
            cycle++;
        }
        return n - cycle;
    }
    void dfs(int u) {
        vis[u] = 1;
        for (auto v : g[u]) if (!vis[v]) dfs(v);
    }
};