#define ll long long
#define N 13
int fact[N];
auto init = []{
    fact[0] = 1;
    for (int i = 1; i < N; i++) fact[i] = fact[i - 1] * i;
    return 0;
}();
class Solution {
public:
    int numSquarefulPerms(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(1 << n, vector<int>(n));
        vector<vector<int>> g(n);
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                ll cur = nums[i] + nums[j];
                ll sq = sqrt(cur);
                if (sq * sq == cur) {
                    g[i].push_back(j);
                    g[j].push_back(i);
                }
            }   
        for (int i = 0; i < n; i++) dp[1 << i][i] = 1;
        for (int mask = 0; mask < (1 << n); mask++)
            for (int u = 0; u < n; u++) if (dp[mask][u])
                for (auto v : g[u]) if (!((mask >> v) & 1))
                    dp[mask | (1 << v)][v] += dp[mask][u];
        int ans = 0;
        int fmask = (1 << n) - 1;
        for (int i = 0; i < n; i++) ans += dp[fmask][i];
        sort(nums.begin(), nums.end());
        for (int i = 0; i < n; ) {
            int cur = nums[i], cnt = 0;
            while (i < n && cur == nums[i]) {
                cnt++;
                i++;
            }
            ans /= fact[cnt];
        }
        return ans;
    }
};