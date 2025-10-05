class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int n = heights.size();
        int m = heights[0].size();
        vector<vector<int>> cnt(n, vector<int>(m));
        deque<pair<int,int>> q;
        vector<vector<bool>> vis(n, vector<bool>(m));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) if (i == 0 || j == 0)
                q.push_front({i, j}), vis[i][j] = 1;
        vector<pair<int,int>> moves = {{1,0},{0,1},{-1,0},{0,-1}};
        auto explore = [&] () -> void {   
            while (q.size()) {
                auto [i, j] = q.back(); q.pop_back();
                cnt[i][j]++;
                for (auto &move : moves) {
                    int I = i + move.first;
                    int J = j + move.second;
                    if (0 <= I && I < n && 0 <= J && J < m && !vis[I][J] && heights[i][j] <= heights[I][J]) {
                        vis[I][J] = 1;
                        q.push_front({I, J});
                    }
                }
            }
        };
        explore();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) vis[i][j] = 0;
        q.clear();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) if (i == n - 1 || j == m - 1)
                q.push_front({i, j}), vis[i][j] = 1;
        explore();
        vector<vector<int>> res;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) if (cnt[i][j] == 2) res.push_back({i, j});
        return res;
    }
};