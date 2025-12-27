class Solution {
public:
    unordered_map<int,vector<int>> g;
    vector<bool> vis;
    vector<int> num, low, color;
    unordered_map<int,int> xToId;
    int cnt = 0, id = 0, timer = 0;
    int N;
    bool has = false;
    int getId(int x) {
        if (!xToId.count(x)) xToId[x] = id++;
        return xToId[x];
    }
    void dfs(int u) {
        vis[u] = 1;
        for (auto v : g[u]) if (!vis[v])
            dfs(v);
    }
    int compo() {
        int ans = 0;
        for (int u = 0; u < cnt; u++) if (!vis[u]) {
            ans++;
            dfs(u);
        }
        return ans;
    }
    void dfs2(int u, int p) {
        color[u] = 1;
        low[u] = num[u] = timer++;
        int c = 0;
        for (auto v : g[u]) if (v != p) {
            if (color[v] == 0) {
                dfs2(v, u);
                low[u] = min(low[u], low[v]);
                if (num[u] <= low[v] && p != -1)
                    has = true;
                c++;
            } else if (color[v] == 1)  {
                low[u] = min(low[u], num[v]);
            }
        }
        if (p == -1 && c >= 2) has = true;
        color[u] = 2;
    }
    int minDays(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        N = n * m;
        vector<pair<int,int>>  moves = {{0,1},{1,0},{0,-1},{-1,0}};
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) if (grid[i][j]) {
                cnt++;
                for (auto &move : moves) {
                    int I = i + move.first;
                    int J = j + move.second;
                    if (0 <= I && I < n && 0 <= J && J < m && grid[I][J]) {
                        g[getId(i * m + j)].push_back(getId(I * m + J));
                    }
                }
            }
        vis.resize(cnt);
        if (compo() >= 2) return 0;
        if (cnt <= 2) return cnt;
        color.resize(cnt);
        low.resize(cnt);
        num.resize(cnt);
        dfs2(0, -1);
        if (has) return 1;
        return 2;
    }
};