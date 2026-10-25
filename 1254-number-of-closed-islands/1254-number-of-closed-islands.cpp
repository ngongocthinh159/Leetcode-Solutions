class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> vis(n, vector<bool>(m));
        vector<pair<int,int>> moves = {{0,1},{1,0},{0,-1},{-1,0}};
        deque<pair<int,int>> q;
        int ans = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) if (!vis[i][j] && grid[i][j] == 0) {
                bool ok = true;
                q.push_front({i, j});
                vis[i][j] = 1;
                while (q.size()) {
                    auto [ii, jj] = q.back();
                    q.pop_back();
                    for (auto &move : moves) {
                        int I = ii + move.first;
                        int J = jj + move.second;
                        if (0 <= I && I < n && 0 <= J && J < m) {
                            if (grid[I][J] == 0 && !vis[I][J]) {
                                vis[I][J] = 1;
                                q.push_front({I, J});
                            }
                        } else
                            ok = false;
                    }
                }
                ans += ok;
            }
        return ans;
    }
};