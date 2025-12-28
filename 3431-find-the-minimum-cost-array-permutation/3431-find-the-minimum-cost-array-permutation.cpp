#define ll long long
#define N 16
#define M 14
const ll base = 16;
ll basepow[N];
pair<int,ll> dp[1 << M][M][M];
int trace[1 << M][M][M];
auto init = [] {
    basepow[0] = 1;
    for (int i = 1; i < N; i++) basepow[i] = basepow[i - 1] * base;
    return 0;
}();
class Solution {
public:
    bool minimize(pair<int, ll> &x, pair<int, ll> &y) {
        if (x > y) {
            x = y;
            return true;
        }
        return false;
    }
    vector<int> findPermutation(vector<int>& nums) {
        int n = nums.size();
        pair<int,ll> SEN = {INT_MAX, LLONG_MAX};
        for (int i = 0; i < (1 << n); i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++) dp[i][j][k] = SEN, trace[i][j][k] = -1;
        for (int i = 0; i < n; i++) dp[1 << i][i][i] = {0, i + 1};
        int fmask = (1 << n) - 1;
        for (int mask = 0; mask < (1 << n); mask++)
            for (int s = 0; s < n; s++)
                for (int u = 0; u < n; u++) if (dp[mask][s][u].first != INT_MAX)
                    for (int v = 0; v < n; v++) if (!((mask >> v) & 1)) {
                        int cost = abs(u - nums[v]);
                        int nmask = mask | (1 << v);
                        if (nmask == fmask) cost += abs(v - nums[s]);
                        auto np = dp[mask][s][u];
                        np.first += cost;
                        np.second = np.second * base + (v + 1);
                        if (minimize(dp[nmask][s][v], np))
                            trace[nmask][s][v] = u;
                    }
        auto ans = SEN;
        int cmask = fmask, S = -1, E = -1;
        for (int s = 0; s < n; s++)
            for (int e = 0; e < n; e++) if (minimize(ans, dp[fmask][s][e])) S = s, E = e;
        vector<int> res;
        res.push_back(E);
        while (trace[cmask][S][E] != -1) {
            int ne = trace[cmask][S][E];
            int ncmask = cmask ^ (1 << E);
            E = ne;
            cmask = ncmask;
            res.push_back(ne);
        }
        reverse(res.begin(), res.end());
        return res;
    }
};