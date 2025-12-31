class Solution {
public:
    int numMagicSquaresInside(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int fmask = (1 << 9) - 1, cnt = 0;
        for (int i = 2; i < n; i++)
            for (int j = 2; j < m; j++) {
                int mask = 0;
                bool ok = 1;
                for (int k = i - 2; k <= i; k++) {
                    int sum = 0;
                    for (int p = j - 2; p <= j; p++) {
                        if (grid[k][p] == 0 || grid[k][p] > 9) {
                            ok = false;
                            break;
                        }
                        mask |= (1 << (grid[k][p] - 1));
                        sum += grid[k][p];
                    }
                    if (sum != 15) {
                        ok = false;
                        break;
                    }
                }
                for (int p = j - 2; p <= j; p++) {
                    int sum = 0;
                    for (int k = i - 2; k <= i; k++) sum += grid[k][p];
                    if (sum != 15)  {
                        ok = false;
                        break;
                    }
                }
                if (grid[i-2][j-2] + grid[i-1][j-1] + grid[i][j] != 15) ok = false;
                if (grid[i][j-2] + grid[i-1][j-1] + grid[i - 2][j] != 15) ok = false;
                if (mask == fmask && ok) cnt++;
            }
        return cnt;
    }
};