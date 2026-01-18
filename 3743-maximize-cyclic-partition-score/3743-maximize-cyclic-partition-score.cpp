class Solution {
public:
    const long long LINF = 1e18 + 5;
    vector<long long> dp, ndp, opt, nopt, cost;
    vector<vector<int>> rmn, rmx;
    void shift_left(vector<int> &arr, int x) {
        x = x % (int) arr.size();
        reverse(arr.begin(), arr.end());
        reverse(arr.begin(), arr.begin() + x);
        reverse(arr.begin() + x, arr.end());
    }
    bool maximize(long long &x, long long y) {
        return  (x < y ? x = y : false);
    }
    int query(int l, int r, vector<vector<int>> &rmq, int mode) {
        int msb = 32 - __builtin_clz(r - l + 1) - 1;
        if (mode == 1)
            return max(rmq[msb][l], rmq[msb][r - (1 << msb) + 1]);
        else
            return min(rmq[msb][l], rmq[msb][r - (1 << msb) + 1]);
    }
    int C(int i, int j) {
        return query(i, j, rmx, 1) - query(i, j, rmn, 2);
    }
    void compute(int l, int r, int optl, int optr) {
        if (l > r) return;

        int m = l + (r - l)/2;
        ndp[m] = dp[m], nopt[m] = opt[m];
        for (int k = optl; k <= min(m, optr); k++) {
            if (maximize(ndp[m], C(k, m) + (k ? dp[k - 1] : 0))) nopt[m] = k;
        }

        compute(l, m - 1, optl, nopt[m]);
        compute(m + 1, r, nopt[m], optr);
    }
    long long solve(vector<int> &nums, int k) {
        int n = nums.size();
        dp.assign(n, 0);
        ndp.assign(n, 0);
        opt.assign(n, 0);
        nopt.assign(n, 0);
        int msb = 32 - __builtin_clz(n) - 1;
        rmn.assign(msb + 1, vector<int>(n, 0));
        rmx.assign(msb + 1, vector<int>(n, 0));
        for (int i = 0; i < n; i++) rmn[0][i] = rmx[0][i] = nums[i]; 
        for (int j = 1; j <= msb; j++)
            for (int i = 0; i + (1 << j) - 1 < n; i++) {
                rmn[j][i] = min(rmn[j - 1][i], rmn[j - 1][i + (1 << (j - 1))]);
                rmx[j][i] = max(rmx[j - 1][i], rmx[j - 1][i + (1 << (j - 1))]);
            }
        for (int i = 0; i < n; i++)
            dp[i] = C(0, i), opt[i] = 0;
        for (int level = 2; level <= k; level++) {
            compute(0, n - 1, 0, n - 1);
            swap(dp, ndp);
            swap(opt, nopt);
        }
        return dp[n - 1];
    }
    long long maximumScore(vector<int>& nums, int k) {
        auto it = min_element(nums.begin(), nums.end());
        int idx = it - nums.begin();
        shift_left(nums, nums.size() - idx);
        long long ans = solve(nums, k);
        shift_left(nums, nums.size() - 1);
        ans = max(ans, solve(nums, k));
        return ans;
    }
};