#define ll long long
#define N 100005
pair<int,ll> dp[N];
auto init = [] {
    for (int i = 1; i < N; i++)
        for (int j = i; j < N; j += i) {
            dp[j].first++;
            dp[j].second += i;
        }
    return 0;
}();
class Solution {
public:
    int sumFourDivisors(vector<int>& nums) {
        int ans = 0;
        for (auto x : nums) if (dp[x].first == 4) ans += dp[x].second;
        return ans;
    }
};