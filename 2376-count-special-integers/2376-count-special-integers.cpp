class Solution {
public:
    int countSpecialNumbers(int n) {
        int b[20]{};
        int len = 0;
        while (n) {
            b[++len] = n%10;
            n /= 10;
        }
        reverse(b + 1, b + len + 1);
        int dp[20][1 << 10][2][2]{};
        dp[0][0][0][0] = 1;
        for (int i = 0; i < len; i++)
            for (int mask = 0; mask < (1 << 10); mask++)
                for (int smaller = 0; smaller < 2; smaller++) 
                    for (int start = 0; start < 2; start++) if (dp[i][mask][smaller][start]) {
                        int upper = smaller ? 9 : b[i + 1];
                        for (int j = 0; j <= upper; j++) if (!((mask >> j) & 1)){
                            int nsmaller = smaller | (j < b[i + 1]);
                            int nstart = start | (j != 0);
                            int nmask = nstart ? (mask | (1 << j)) : 0;
                            dp[i + 1][nmask][nsmaller][nstart] += dp[i][mask][smaller][start];
                        }
                    }
        int ans = 0;
        for (int mask = 1; mask < (1 << 10); mask++)
            for (int smaller = 0; smaller < 2; smaller++) ans += dp[len][mask][smaller][1];
        return ans;
    }
};