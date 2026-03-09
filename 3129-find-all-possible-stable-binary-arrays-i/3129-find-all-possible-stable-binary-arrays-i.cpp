#define N 205
int dp[N][N][2], pref[N][N][2], pref2[N][N][2];
class Solution {
public:
    const int MOD = 1e9 + 7;
    void add(int &x, int y) {
        x += y;
        if (x >= MOD) x -= MOD;
    }
    void sub(int &x, int y) {
        x -= y;
        if (x < 0) x += MOD;
    }
    int numberOfStableArrays(int zero, int one, int limit) {
        int n = zero + one;
        for (int o = 0; o <= one + 2; o++)
            for (int z = 0; z <= zero + 2; z++)
                for (int j = 0; j < 2; j++)
                    dp[o][z][j] = pref[o][z][j] = pref2[o][z][j] = 0;
        
        // dp[0][0][1] = dp[0][0][0] = 1;
        // pref[0 + 1][0][1] = pref[0][0][1] + dp[0][0][1];
        // pref[0][0 + 1][0] = pref[0][0][0] + dp[0][0][0];

        for (int o = 0; o <= one; o++)
            for (int z = 0; z <= zero; z++)
                for (int j = 0; j < 2; j++) {
                    // if ((o == 0 && z == 1) || (o == 1 && z == 0)) continue;
                    if (o == 0 && z == 0) {
                        dp[o][z][j] = 1;
                    } else {
                        if (j == 1) {
                            int mx = min(limit, o);
                            add(dp[o][z][j], pref[o][z][0]); // dp[o - 1 -> o - mx][z][0]
                            sub(dp[o][z][j], pref[o - mx][z][0]);
                        }
                        else {
                            int mx = min(limit, z);
                            add(dp[o][z][j], pref2[o][z][1]);
                            sub(dp[o][z][j], pref2[o][z - mx][1]);
                        }
                    }

                    pref[o + 1][z][j] = pref[o][z][j];
                    add(pref[o + 1][z][j], dp[o][z][j]);
                    pref2[o][z + 1][j] = pref2[o][z][j];
                    add(pref2[o][z + 1][j], dp[o][z][j]);
                }
        int ans = 0;
        add(ans, dp[one][zero][0]);
        add(ans, dp[one][zero][1]);
        return ans;
    }
};