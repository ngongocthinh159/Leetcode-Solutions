class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int N = strs.size();
        vector<pair<int,int>> v(N);
        for (int i = 0; i < N; i++) {
            int z = 0, o = 0;
            for (auto c : strs[i]) {
                if (c == '0') z++;
                else o++;
            }
            v[i] = {z, o};
        }
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int i = 0; i < N; i++) {
            vector<vector<int>> ndp = dp;
            int Z = v[i].first;
            int O = v[i].second;
            for (int z = 0; z <= m; z++)
                for (int o = 0; o <= n; o++) if (z >= Z && o >= O)
                    ndp[z][o] = max(ndp[z][o], 1 + dp[z - Z][o - O]);
            swap(dp, ndp);
        }
        int ans = 0;
        for (int z = 0; z <= m; z++)
            for (int o = 0; o <= n; o++) ans = max(ans, dp[z][o]);
        return ans;
    }
};