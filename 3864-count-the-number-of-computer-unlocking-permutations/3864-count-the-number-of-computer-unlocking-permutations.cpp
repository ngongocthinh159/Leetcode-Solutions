#define N 100005
int fact[N];
const int MOD = 1e9 + 7;
auto init = []{
    fact[0] = 1;
    for (int i = 1; i < N; i++) fact[i] = 1LL * fact[i - 1] * i % MOD;
    return 0;
}();
class Solution {
public:
    int countPermutations(vector<int>& complexity) {
        int n = complexity.size();
        for (int i = 1; i < n; i++) if (complexity[i] <= complexity[0]) return 0;
        return fact[n - 1];
    }
};