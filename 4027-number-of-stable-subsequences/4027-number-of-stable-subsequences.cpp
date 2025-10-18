#define ll long long
const int MOD = 1e9 + 7;
class Solution {
public:
    void add(ll &x, ll y) {
        x += y;
        if (x >= MOD) x -= MOD;
    }
    bool ok(int x, int y, int z) {
        return !(x == y && y == z);
    }
    int countStableSubsequences(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 1;
        if (n == 2) return 3;
        vector<vector<vector<ll>>> dp(n,
            vector<vector<ll>>(2,
                vector<ll>(2)));
        dp[1][nums[0] & 1][nums[1] & 1] = 1;
        int odd = 0, even = 0;
        for (int i = 0; i < 2; i ++) {
            if (nums[i] & 1)
                odd++;
            else
                even++;
        }
        for (int i = 1; i < n - 1; i++) {
            for (int j = 0; j < 2; j++)
                for (int k = 0; k < 2; k++) if (dp[i][j][k]) {
                    add(dp[i + 1][j][k], dp[i][j][k]);
                    if (ok(j, k, nums[i + 1] & 1))
                        add(dp[i + 1][k][nums[i + 1] & 1], dp[i][j][k]);
                }
            add(dp[i + 1][0][nums[i + 1] & 1], even);
            add(dp[i + 1][1][nums[i + 1] & 1], odd);
            if (nums[i + 1] & 1)
                odd++;
            else
                even++;
        }
        ll ans = 0;
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++) add(ans, dp[n - 1][j][k]);
        add(ans, n);
        return ans;
    }
};