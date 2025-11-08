#define N 100005
int spf[N], buf[N], top = 0;
auto init = [] {
    for (int i = 0; i < N; i++) spf[i] = i;
    for (int i = 2; i * i < N; i++) if (spf[i] == i)
        for (int j = i * i; j < N; j += i) spf[j] = min(spf[j], i);
    return 0;
}();
string factorize(int x) {
    string cur = "";
    while (x != 1) {
        int fact = spf[x], cnt = 0;
        while (x % fact == 0) x /= fact, cnt++;
        if (cnt&1)
            cur += to_string(fact) + ",";
    }
    return cur;
}
class Solution {
public:
    vector<vector<int>> g;
    vector<int> ans;
    unordered_map<string,int> f;
    void dfs(int u, int p, vector<int> &nums) {
        string k = factorize(nums[u]);
        int &cnt = f[k];
        ans[u] = cnt;
        cnt++;
        for (auto v : g[u]) if (v != p)
            dfs(v, u, nums);
        cnt--;
    }
    long long sumOfAncestors(int n, vector<vector<int>>& edges, vector<int>& nums) {
        g.resize(n);
        ans.resize(n);
        for (auto  &e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        dfs(0, -1, nums);
        long long res = 0;
        for (auto x : ans) res += x;
        return res;
    }
};