#define MX 100
#define BIT 30
bitset<MX> prime;
auto init = []{
    prime.flip();
    prime[0] = prime[1] = 0;
    for (int i = 2; i < MX; i++) if (prime[i])
        for (int j = i * i; j < MX; j += i) prime[j] = false;
    return  0;
}();
class Solution {
public:
    int cnt(int x) {
        int dp[BIT + 1][BIT + 1][2]{};
        dp[BIT][0][0] = 1;
        for (int bit = BIT; bit >= 1; bit--) 
            for (int chosen = 0; chosen < BIT; chosen++)
                for (int smaller = 0; smaller < 2; smaller++) if (dp[bit][chosen][smaller]) {
                    int xbit = (x >> (bit - 1)) & 1;
                    int upper = smaller ? 1 : xbit;
                    for (int j = 0; j <= upper; j++) {
                        int nchosen = chosen + j;
                        int nsmaller = smaller | (j < xbit);
                        dp[bit - 1][nchosen][nsmaller] += dp[bit][chosen][smaller];
                    }
                }
        int ans = 0;
        for (int chosen = 0; chosen < BIT; chosen++) if (prime[chosen]) {
            ans += dp[0][chosen][0];
            ans += dp[0][chosen][1];
        }
        return ans;
    }
    int countPrimeSetBits(int left, int right) {
        return cnt(right) - cnt(left - 1);
    }
};