class Solution {
public:
    map<array<int,2>,int> color;
    vector<vector<int>> moves = {{1,0},{0,1},{-1,0},{0,-1}};
    bool ok = false;
    void dfs(int i, int j, char c, int prevI, int prevJ, vector<vector<char>> &grid) {
        color[{i,j}] = 1;
        for (auto &move : moves) {
            int I = i + move[0];
            int J = j + move[1];
            if (0 <= I && I < int(grid.size()) && 0 <= J && J < int(grid[0].size()) && grid[I][J] == c) {
                if (I == prevI && J == prevJ) continue;
                if (color[{I,J}] == 0) {
                    dfs(I, J, c, i, j, grid);
                } else if (color[{I,J}] == 1) ok = true;
            }
        }
        color[{i,j}] = 2;
    }
    bool containsCycle(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) if (color[{i, j}] == 0) {
                dfs(i, j, grid[i][j], -1, -1, grid);
            }
        return ok;
    }
};