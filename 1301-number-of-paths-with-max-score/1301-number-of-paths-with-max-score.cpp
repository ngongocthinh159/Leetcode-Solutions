class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size(), m = board[0].size();
        const int MOD = 1e9 + 7;
        vector<vector<array<int,2>>> dp(n, vector<array<int,2>>(m, {-1,0}));
        dp[n - 1][m - 1] = {0, 1};
        vector<array<int,2>> moves = {{-1,0},{0,-1},{-1,-1}};
        for (int i = n - 1; i >= 0; i--)
            for (int j = m - 1; j >= 0; j--) if (dp[i][j][0] != -1) {
                for (auto &move : moves) {
                    int I = i + move[0];
                    int J = j + move[1];
                    if (0 <= I && I < n && 0 <= J && J < m && board[I][J] != 'X') {
                        int cost = board[I][J] == 'E' ? 0 : (board[I][J] - '0');
                        if (dp[I][J][0] < cost + dp[i][j][0]) {
                            dp[I][J][0] = cost + dp[i][j][0];
                            dp[I][J][1] = dp[i][j][1];
                        } else if (dp[I][J][0] == cost + dp[i][j][0]) {
                            dp[I][J][1] += dp[i][j][1];
                            dp[I][J][1] %= MOD;
                        }
                    }
                }
            }
        if (dp[0][0][0] == -1) return {0, 0};
        return {dp[0][0][0], dp[0][0][1]};
    }
};