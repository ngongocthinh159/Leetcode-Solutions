#define ll long long
#define N 17
ll dp[N][10][2][3][2], cnt[N][10][2][3][2];
bool ok[N][10][2][3][2];
class Solution {
public:
    ll cal(long long x) {
        string s = to_string(x);
        int n = s.size();
         for (int i = 0; i < n; i++)
            for (int cdigit = 0; cdigit <= 9; cdigit++)
                for (int smaller = 0; smaller < 2; smaller++)
                    for (int prev = 0; prev < 3; prev++)
                        for (int start = 0; start < 2; start++)
                            dp[i][cdigit][smaller][prev][start] = cnt[i][cdigit][smaller][prev][start] = 0;
        for (int j = 0; j <= 9; j++) if (j <= (s[0] - '0'))
            cnt[0][j][j < (s[0] - '0')][2][j != 0] = 1;
        for (int i = 0; i < n - 1; i++)
            for (int cdigit = 0; cdigit <= 9; cdigit++)
                for (int smaller = 0; smaller < 2; smaller++)
                    for (int prev = 0; prev < 3; prev++)
                        for (int start = 0; start < 2; start++) {
                            int upper = smaller ? 9 : (s[i + 1] - '0');
                            for (int ndigit = 0; ndigit <= upper; ndigit++) {
                                int nsmaller = smaller || (ndigit < (s[i + 1] - '0'));
                                int nprev;
                                if (start) 
                                    nprev = cdigit == ndigit ? 2 : (cdigit > ndigit ? 0 : 1);
                                else
                                    nprev = 2;
                                int nstart = start || (ndigit != 0);
                                int cost = ((prev == 0 && nprev == 1) || (prev == 1 && nprev == 0) ? 1 : 0);
                                cnt[i + 1][ndigit][nsmaller][nprev][nstart] += cnt[i][cdigit][smaller][prev][start];
                                dp[i + 1][ndigit][nsmaller][nprev][nstart] += dp[i][cdigit][smaller][prev][start] 
                                                                    + cost * cnt[i][cdigit][smaller][prev][start];
                            }
                        }
        ll ans = 0;
        for (int cdigit = 0; cdigit <= 9; cdigit++)
            for (int smaller = 0; smaller < 2; smaller++)
                for (int prev = 0; prev < 3; prev++)
                    ans += dp[n - 1][cdigit][smaller][prev][1];
        return ans;
    }
    long long totalWaviness(long long num1, long long num2) {        
        return cal(num2) - cal(num1 - 1);
    }
};