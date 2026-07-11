class Solution {
public:
    vector<vector<int>> g;
    vector<bool> visited;
    int e_cnt, v_cnt;
    void dfs(int u, vector<vector<int>>& edges) {
        v_cnt++;
        e_cnt += g[u].size();
        visited[u] = true;
        for (auto i : g[u]) {
            int v = edges[i][0] ^ edges[i][1] ^ u;
            if (!visited[v])
                dfs(v, edges);
        }
    }
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        g.resize(n);
        visited.resize(n);
        for (int i = 0; i < edges.size(); i++) {
            g[edges[i][0]].push_back(i);
            g[edges[i][1]].push_back(i);
        }
        int ans = 0;
        for (int i = 0; i < n; i++) if (!visited[i]) {
            e_cnt = v_cnt = 0;
            dfs(i, edges);
            if (v_cnt*(v_cnt - 1) == e_cnt) ans++;
        }
        return ans;
    }
};