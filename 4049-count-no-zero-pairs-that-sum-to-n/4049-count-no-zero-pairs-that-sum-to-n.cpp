#define N 20
long long dp[N][2][2][2];
vector<int> list1 = {0};
vector<int> list2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
class Solution {
public:
    long long countNoZeroPairs(long long x) {
        string s = to_string(x);
        reverse(s.begin(), s.end());
        int n = s.size();
        for (int i = 0; i <= n; i++)
            for (int j = 0; j < 2; j++)
                for (int k = 0; k < 2; k++)
                    for (int p = 0; p < 2; p++) dp[i][j][k][p] = 0;
        dp[0][0][0][0] = 1;
        for (int i = 0; i < n; i++)
            for (int f1 = 0; f1 < 2; f1++)
                for (int f2 = 0; f2 < 2; f2++)
                    for (int carry = 0; carry < 2; carry++) if (dp[i][f1][f2][carry]) {
                        auto &list = f1 ? list1 : list2;
                        for (auto d1 : list) {
                            int d2 = s[i] - '0' - (d1 + carry);
                            int ncarry = 0;
                            if (d2 < 0) {
                                ncarry = 1;
                                d2 += 10;
                            }
                            if (f2) {
                                if (d2 != 0) continue;
                                if (f1)
                                    dp[i + 1][f1][f2][ncarry] += dp[i][f1][f2][carry];
                                else {
                                    dp[i + 1][1][f2][ncarry] += dp[i][f1][f2][carry];
                                    dp[i + 1][0][f2][ncarry] += dp[i][f1][f2][carry];
                                }
                            } else {
                                if (d2 == 0) continue;
                                if (f1) {
                                    dp[i + 1][f1][0][ncarry] += dp[i][f1][f2][carry];
                                    dp[i + 1][f1][1][ncarry] += dp[i][f1][f2][carry];
                                } else {
                                    dp[i + 1][0][0][ncarry] += dp[i][f1][f2][carry];
                                    dp[i + 1][1][0][ncarry] += dp[i][f1][f2][carry];
                                    dp[i + 1][0][1][ncarry] += dp[i][f1][f2][carry];
                                    dp[i + 1][1][1][ncarry] += dp[i][f1][f2][carry];
                                }
                            }
                        }
                    }
        return dp[n][1][1][0];
    }
};