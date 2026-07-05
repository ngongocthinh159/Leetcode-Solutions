#define N 105
int dp[N][N][N][2][2];
class Solution {
public:
    const int MOD = 1e9 + 7;
    void add(int &x, int y) {
        x += y;
        if (x >= MOD) x -= MOD;
    }
    int interleaveCharacters(string word1, string word2, string target) {
        int x = word1.size();
        int y = word2.size();
        int z = target.size();
        for (int i = 0; i <= x; i++)
            for (int j = 0; j <= y; j++)
                for (int k = 0; k <= z; k++)
                    for (int c1 = 0; c1 < 2; c1++)
                        for (int c2 = 0; c2 < 2; c2++) dp[i][j][k][c1][c2] = 0;
        dp[0][0][0][0][0] = 1;
        for (int i = 0; i <= x; i++)
            for (int j = 0; j <= y; j++)
                for (int k = 0; k < z; k++)
                    for (int c1 = 0; c1 < 2; c1++)
                        for (int c2 = 0; c2 < 2; c2++) if (dp[i][j][k][c1][c2]) {
                            for (int p = i; p < x; p++) if (word1[p] == target[k]) {
                                add(dp[p + 1][j][k + 1][1][c2], dp[i][j][k][c1][c2]);
                            }
                            for (int p = j; p < y; p++) if (word2[p] == target[k]) {
                                add(dp[i][p + 1][k + 1][c1][1], dp[i][j][k][c1][c2]);
                            }
                        }
        int ans = 0;
        for (int i = 0; i <= x; i++)
            for (int j = 0; j <= y; j++) add(ans, dp[i][j][z][1][1]);
        return ans;
    }
};