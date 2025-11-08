#define N 100005
int spf[N], buf[N], top = 0;
string toKey[N];
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
auto init = [] {
    for (int i = 0; i < N; i++) spf[i] = i;
    for (int i = 2; i * i < N; i++) if (spf[i] == i)
        for (int j = i * i; j < N; j += i) spf[j] = min(spf[j], i);
    for (int i = 1; i < N; i++) toKey[i] = factorize(i);
    return 0;
}();
class Solution {
public:
    vector<vector<int>> g;
    long long res = 0;
    unordered_map<string,int> f;
    void dfs(int u, int p, vector<int> &nums) {
        string k = toKey[nums[u]];
        int &cnt = f[k];
        res += cnt;
        cnt++;
        for (auto v : g[u]) if (v != p)
            dfs(v, u, nums);
        cnt--;
    }
    long long sumOfAncestors(int n, vector<vector<int>>& edges, vector<int>& nums) {
        g.resize(n);
        for (auto  &e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        dfs(0, -1, nums);
        return res;
    }
};