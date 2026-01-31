class Solution {
public:
    const int IINF = 1e9 + 5;
    int solve(string &s, int x) {
        int n = s.size();
        int cnt[27]{};
        for (auto c : s) cnt[c - 'a' + 1]++;
        vector<vector<pair<int,int>>> dp(27, vector<pair<int,int>>(2));
        dp[0][0] = {0, 0};
        dp[0][1] = {IINF, IINF};
        for (int i = 1; i < 27; i++) {
            if (cnt[i] == x || cnt[i] == 0) dp[i][1] = {IINF, IINF};
            else {
                int cost = cnt[i] > x ? cnt[i] - x : cnt[i];
                dp[i][1] = {min(dp[i - 1][0].first, dp[i - 1][1].first) + cost, cost}; 
            }

            if (cnt[i] == x || cnt[i] == 0) dp[i][0] = {min(dp[i - 1][0].first, dp[i - 1][1].first), 0};
            else {
                if (cnt[i] > x) dp[i][0] = {IINF, IINF};
                else {
                    int u = x - cnt[i] + min(dp[i - 1][0].first, dp[i - 1][1].first); 
                    if (dp[i - 1][1].first != IINF) {
                        u = min(u, max(0, x - cnt[i] - dp[i - 1][1].second) + dp[i - 1][1].first);
                    }
                    dp[i][0] = {u, 0};
                }
            }
        }
        return min(dp[26][0].first, dp[26][1].first);
    }
    int makeStringGood(string s) {
        int n = s.size();
        int cnt[26]{}, mx = -1, mn = INT_MAX, ans = INT_MAX;
        for (auto c : s) cnt[c - 'a']++, mx = max(mx, cnt[c - 'a']), mn = min(mn, cnt[c - 'a']);
        for (int i = mn; i <= mx; i++) {
            ans = min(ans, solve(s, i));
        }
        return ans;
    }
};