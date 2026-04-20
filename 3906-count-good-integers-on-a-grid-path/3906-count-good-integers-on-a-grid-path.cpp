class Solution {
public:
    set<int> S;
    string d;
    vector<vector<vector<long long>>> dp;
    long long dfs(int i, int smaller, int last, vector<int> &b) {
        if (i >= b.size()) return 1;
        if (dp[i][smaller][last] != -1) return dp[i][smaller][last];
        int upper = smaller ? 9 : b[i];
        int lower = S.count(i) ? last : 0;
        long long res = 0;
        for (int j = lower; j <= upper; j++) {
            int nsmaller = smaller | (j < b[i]);
            int nlast = S.count(i) ? j : last;
            res += dfs(i + 1, nsmaller, nlast, b);
        }
        return dp[i][smaller][last] = res;
    }
    long long solve(long long x) {
        vector<int> b;
        while (x) {
            b.push_back(x % 10);
            x /= 10;
        }
        while (b.size() < 16) b.push_back(0);
        reverse(b.begin(), b.end());

        for (int i = 0; i < int(b.size()); i++)
            for (int smaller = 0; smaller < 2; smaller++)
                for (int last = 0; last < 10; last++) 
                    dp[i][smaller][last] = -1;
        // cout << dfs(15, 0, 1, )
        return dfs(0, 0, 0, b);
    }
    long long countGoodIntegersOnPath(long long l, long long r, string directions) {
        d = directions;
        int i = 0, j = 0;
        S.insert(0);
        for (auto c : directions) {
            if (c == 'D') i++;
            else j++;
            S.insert(4*i + j);
            // cout << i << ' ' << j << '\n';
        }
        dp.assign(20, vector<vector<long long>>(2, vector<long long>(10)));
        // cout << solve(r) << '\n';
        return solve(r) - solve(l - 1);    
    }
};