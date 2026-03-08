class Solution {
public:
    vector<int> pref;
    int n;
    unordered_map<int,unordered_map<int,long long>> dp;
    long long E, F;
    long long getCost(int l, int r) {
        int cnt = pref[r + 1] - pref[l];
        if (cnt == 0) return F;
        return E * (r - l + 1) * cnt; 
    }
    long long dfs(int l, int r) {
        if (l == r) return getCost(l, r);

        int len = r - l + 1;
        long long res = getCost(l, r);
        if (len&1) return res;
        int m = (l + r) / 2;
        res = min(res, dfs(l, m) + dfs(m + 1, r));
        return res;
    }
    long long minCost(string s, int encCost, int flatCost) {
        E = encCost;
        F = flatCost;
        n = s.size();
        pref.resize(n + 1);
        for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + s[i] - '0';
        return dfs(0, n - 1);
    }
};