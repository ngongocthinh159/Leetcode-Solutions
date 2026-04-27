class Solution {
public:
    set<pair<int,int>> active;
    vector<vector<array<int,2>>> moves = {
        {},
        {{0,-1}, {0,1}},
        {{-1,0}, {1,0}},
        {{0,-1}, {1,0}},
        {{0,1}, {1,0}},
        {{-1,0}, {0,-1}},
        {{-1,0}, {0,1}},
    };
    bool ok;
    void dfs(int i, int j, vector<vector<int>> &grid) {
        if (i == int(grid.size() - 1) && j == int(grid[0].size() - 1)) {
            ok = true;
            return;
        }
        active.insert({i,j});
        for (auto &move : moves[grid[i][j]]) {
            int I = i + move[0];
            int J = j + move[1];
            if (0 <= I && I < int(grid.size()) && 0 <= J && J < int(grid[0].size()) && !active.count({I, J})) {
                bool can = false;
                for (auto &move1 : moves[grid[I][J]]) {
                    int II = I + move1[0];
                    int JJ = J + move1[1];
                    if (II == i && JJ == j) {
                        can = true;
                        break;
                    }
                }
                if (can)
                    dfs(I, J, grid);
                if (ok) break;
            }
        }
        active.erase({i,j});
    }
    bool hasValidPath(vector<vector<int>>& grid) {
        ok = false;
        dfs(0,0,grid);
        return ok;
    }
};