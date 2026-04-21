class Solution {
public:
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        int n = source.size();
        vector<vector<int>> g(n);
        for (auto  &s : allowedSwaps) {
            g[s[0]].push_back(s[1]);
            g[s[1]].push_back(s[0]);
        }
        vector<bool> vis(n);
        int ans = 0;
        for (int i = 0; i < n; i++) if (!vis[i]) {
            vector<int> a,b;
            dfs(i, source, target, a, b, vis, g);
            sort(a.begin(), a.end());
            sort(b.begin(), b.end());
            {
                int m = a.size();
                int j = 0, k = 0;
                while (j < m && k < m) {
                    if (a[j] == b[k]) {
                        j++;
                        k++;
                        ans++;
                    } else if (a[j] < b[k]) {
                        j++;
                    } else {
                        k++;
                    }
                }
            }
        }
        return n - ans;
    }
    void dfs(int u, vector<int> &s, vector<int> &t, vector<int> &a, vector<int> &b, vector<bool> &vis, vector<vector<int>> &g) {
        vis[u] = 1;
        a.push_back(s[u]);
        b.push_back(t[u]);
        for (auto v : g[u]) if (!vis[v])
            dfs(v, s, t, a, b, vis, g);
    }
};