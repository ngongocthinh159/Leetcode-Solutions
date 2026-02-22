#define ll long long
class Solution {
public:
    vector<unordered_map<int,unordered_map<int,unordered_map<int,int>>>> dp;
    int n;
    pair<int, long long> find(int x, long long X) {
        int cnt = 0;
        while (X % x == 0) X /= x, cnt++;
        return {cnt, X};
    }
    long long dfs(int i, int c2, int c3, int c5, vector<int> &nums) {
        if (i == n)
            return c2 == 0 && c3 == 0 && c5 == 0;
        if (dp[i].count(c2) && dp[i][c2].count(c3) && dp[i][c2][c3].count(c5)) return dp[i][c2][c3][c5];

        int a = find(2, nums[i]).first;
        int b = find(3, nums[i]).first;
        int c = find(5, nums[i]).first;
        long long res = dfs(i + 1, c2, c3, c5, nums) +
                        dfs(i + 1, c2 - a, c3 - b, c5 - c, nums) + 
                        dfs(i + 1, c2 + a, c3 + b, c5 + c, nums);

        return dp[i][c2][c3][c5] = res;
    }
    int countSequences(vector<int>& nums, long long k) {
        n = nums.size();
        dp.resize(n);
        auto [c2, x] = find(2, k);
        auto [c3, y] = find(3, x);
        auto [c5, z] = find(5, y);
        if (z != 1) return 0;
        return dfs(0, c2, c3, c5, nums);
    }
};