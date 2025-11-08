class Solution {
public:
    vector<int> color;
    int dist(vector<int> &p1, vector<int> &p2) {
        return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]);
    }
    bool dfs(int u, int c, vector<vector<int>> &g) {
        color[u] = c;
        for (auto v : g[u]) {
            if (color[v] == -1) {
                if (!dfs(v, !c, g)) return false;
            } else if (color[v] == color[u]) return false;
        }
        return true;
    }
    bool is_bipartile(vector<vector<int>> &g) {
        int n = g.size();
        color.assign(n, -1);
        for (int i = 0; i < n; i++) if (color[i] == -1) {
            if (!dfs(i, 0, g)) return false;
        }
        return true;
    }
    bool check(int x, vector<vector<int>> &ps) {
        int n = ps.size();
        vector<vector<int>> g(n);
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) if (dist(ps[i], ps[j]) < x) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        return is_bipartile(g);
    }
    int maxPartitionFactor(vector<vector<int>>& points) {
        int n = points.size();
        if (n == 2) return 0;
        int l = -1, r = 5e8 + 105;
        while (r - l > 1) {
            int m = l + (r - l)/2;
            if (check(m, points))
                l = m;
            else 
                r = m;
        }
        return l;
    }
};