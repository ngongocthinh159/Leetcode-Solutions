class Solution {
public:
    void shift_right(vector<pair<int,int>> &v, int k) {
        shift_left(v, int(v.size()) - k);
    }
    void shift_left(vector<pair<int,int>> &v, int k) {
        reverse(v.begin(), v.begin() + k);
        reverse(v.begin() + k, v.end());
        reverse(v.begin(), v.end());
    }
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> v = grid;
        vector<pair<int,int>> dir = {{1,0},{0,1},{-1,0},{0,-1}};
        for (int startI = 0, endI = n - 1, startJ = 0, endJ = m - 1; ; startI++, endI--, startJ++, endJ--) {
            if (!(startI <= endI && startJ <= endJ)) break;

            int I = startI, J = startJ;
            int didx = 0;
            vector<pair<int,int>> cur;
            while (1) {
                if ((startI <= I && I <= endI) && (startJ <= J && J <= endJ)) {
                    if (!(didx == 3 && I == startI && J == startJ))
                        cur.push_back({I, J});
                    I += dir[didx].first;
                    J += dir[didx].second;
                } else {
                    I -= dir[didx].first;
                    J -= dir[didx].second;

                    didx++;
                    if (didx == 4) break;

                    I += dir[didx].first;
                    J += dir[didx].second;
                }
            }
            didx = 0;
            int K = k;
            K = K % int(cur.size());
            shift_right(cur, K);
            
            int p = 0;
            while (1) {
                if ((startI <= I && I <= endI) && (startJ <= J && J <= endJ)) {
                    if (!(didx == 3 && I == startI && J == startJ)) {
                        v[I][J] = grid[cur[p].first][cur[p].second];
                        p++;
                    }
                    I += dir[didx].first;
                    J += dir[didx].second;
                } else {
                    I -= dir[didx].first;
                    J -= dir[didx].second;

                    didx++;
                    if (didx == 4) break;

                    I += dir[didx].first;
                    J += dir[didx].second;
                }
            }
        }
        return v;
    }
};