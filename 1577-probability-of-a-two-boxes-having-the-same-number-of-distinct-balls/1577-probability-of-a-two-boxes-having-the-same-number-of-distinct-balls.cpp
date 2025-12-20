#define N 55
#define ll long long
double fact[N];
auto init = [] {
    fact[0] = 1;
    for (int i = 1; i < N; i++) fact[i] = fact[i - 1] * i;
    return 0;
}();
class Solution {
public:
    vector<int> f;
    int n, k;
    double dfs(int i, int take, int d1, int d2, double c1, double c2) {
        if (take > n) return 0;
        if (i == k) {
            if (take != n) return 0;
            if (d1 != d2) return 0;
            return c1 * c2;
        }
        double res = 0;
        for (int j = 0; j <= f[i]; j++) {
            int nd1 = d1 + (j != 0);
            int nd2 = d2 + (j != f[i]);
            res += dfs(i + 1, take + j, nd1, nd2, c1 / fact[j], c2 / fact[f[i] - j]);
        }
        return res;
    }
    double getProbability(vector<int>& balls) {
        k = balls.size();
        f = balls;
        for (int i = 0; i < balls.size(); i++) n+= balls[i];
        n /= 2;
        
        double denom = fact[2*n];
        for (int i = 0; i < k; i++) {
            denom = denom / fact[f[i]];
        }

        return dfs(0, 0, 0, 0, fact[n], fact[n]) / denom;
    }
};