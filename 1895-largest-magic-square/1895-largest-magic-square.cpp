class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> col(n, vector<int>(m));
        vector<vector<int>> row(n, vector<int>(m));
        vector<vector<int>> d1(n, vector<int>(m));
        vector<vector<int>> d2(n, vector<int>(m));
        for (int i = 0; i < n; i++)
            for (int j = m - 1; j >= 0; j--) {
                d2[i][j] = grid[i][j] + ((i - 1 >= 0 && j + 1 < m) ? d2[i - 1][j + 1] : 0);
            }
        int ans = 1;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                row[i][j] = grid[i][j] + (j - 1 >= 0 ? row[i][j - 1] : 0);
                col[i][j] = grid[i][j] + (i - 1 >= 0 ? col[i - 1][j] : 0);
                d1[i][j] = grid[i][j] + ((i - 1 >= 0 && j - 1 >= 0) ? d1[i - 1][j - 1] : 0);
                for (int k = 2; k <= 1 + min(i, j); k++) {
                    int ei = i, si = ei - k + 1, ej = j, sj = ej - k + 1;
                    int sum1 = d2[ei][sj] - ((si - 1 >= 0 && ej + 1 < m) ? d2[si - 1][ej + 1] : 0);
                    int sum2 = d1[ei][ej] - ((si - 1 >= 0 && sj - 1 >= 0) ? d1[si - 1][sj - 1] : 0);
                    if (sum1 != sum2) continue;
                    bool ok = true;
                    for (int jj = sj; jj <= ej; jj++) {
                        int cur = col[ei][jj] - (si - 1 >= 0 ? col[si - 1][jj] : 0);
                        if (cur != sum1) {
                            ok = false;
                            break;
                        }
                    }
                    for (int ii = si; ii <= ei; ii++) {
                        int cur = row[ii][ej] - (sj - 1 >= 0 ? row[ii][sj - 1] : 0);
                        if (cur != sum1) {
                            ok = false;
                            break;
                        }
                    }
                    if (ok)
                        ans = max(ans, k);
                }
            }
        return ans;
    }
};