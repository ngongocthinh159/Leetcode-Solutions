class Solution {
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<array<int,2>>> moves = {
            {},
            {{0,-1}, {0,1}},
            {{-1,0}, {1,0}},
            {{0,-1}, {1,0}},
            {{0,1}, {1,0}},
            {{-1,0}, {0,-1}},
            {{-1,0}, {0,1}},
        };
        vector<vector<int>> g(n*m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                for (auto &move : moves[grid[i][j]]) {
                    int I = i + move[0];
                    int J = j + move[1];
                    if (0 <= I && I < n && 0 <= J && J < m) {
                        for (auto &move1 : moves[grid[I][J]]) {
                            int II = I + move1[0];
                            int JJ = J + move1[1];
                            if (II == i && JJ == j) {
                                g[i*m + j].push_back(I*m + J);
                            }
                        }
                    }
                }
            }
        vector<bool> vis(n*m);
        vis[0] = 1;
        deque<int> q;
        q.push_front(0);
        while (q.size()) {
            for (int sz = q.size(); sz; sz--) {
                int u = q.back(); q.pop_back();
                for (auto v : g[u]) if (!vis[v]) {
                    vis[v] = 1;
                    q.push_front(v);
                }
            }
        }
        return vis[(n - 1) * m + m - 1];
    }
};