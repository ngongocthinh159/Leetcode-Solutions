#define N 20
long long dp[N][N][N][2];
vector<int> list1 = {0};
vector<int> list2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
class Solution {
public:
    long long cnt(string &s) {
        reverse(s.begin(), s.end());
        int n = s.size();
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++)
                for (int k = 0; k <= n; k++)
                    for (int p = 0; p < 2; p++) dp[i][j][k][p] = 0;
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                dp[0][j][k][0] = 1;
        for (int i = 0; i < n; i++)
            for (int l1 = 1; l1 <= n; l1++)
                for (int l2 = 1; l2 <= n; l2++)
                    for (int carry = 0; carry < 2; carry++) if (dp[i][l1][l2][carry]) {
                        auto &list = (i + 1) > l1 ? list1 : list2;
                        for (auto d1 : list) {
                            int d2 = s[i] - '0' - (d1 + carry);
                            int ncarry = 0;
                            if (d2 < 0) {
                                ncarry = 1;
                                d2 += 10;
                            }
                            if ((i + 1) > l2 && d2 != 0) continue;
                            if ((i + 1) <= l2 && d2 == 0) continue;
                            dp[i + 1][l1][l2][ncarry] += dp[i][l1][l2][carry];
                        }
                    }
        long long ans = 0;
        for (int l1 = 1; l1 <= n; l1++)
            for (int l2 = 1; l2 <= n; l2++)
                ans += dp[n][l1][l2][0];
        return ans;
    }
    long long countNoZeroPairs(long long x) {
        string s = to_string(x);
        return cnt(s);
    }
};