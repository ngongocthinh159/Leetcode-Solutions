class Solution {
public:
    vector<string> states; 
    vector<vector<int>> g;
    int sz;
    const int MOD = 1e9 + 7;
    bool ok(string &s, string &t) {
        int n = s.size();
        for (int i = 0; i < n; i++) if (s[i] == t[i]) return false;
        return true;
    }
    void add(int &x, int y) {
        x+=y;
        if (x>=MOD) x-=MOD;
    }
    int numOfWays(int n) {
        states.push_back("RGR");
        states.push_back("RGB");
        states.push_back("RBR");
        states.push_back("RBG");
        states.push_back("BRB");
        states.push_back("BRG");
        states.push_back("BGB");
        states.push_back("BGR");
        states.push_back("GBG");
        states.push_back("GBR");
        states.push_back("GRG");
        states.push_back("GRB");
        sz = states.size();
        g.resize(sz);
        for (int i = 0; i < sz; i++)
            for (int j = 0; j < i; j++) if (ok(states[i], states[j])) g[i].push_back(j), g[j].push_back(i);
        vector<int> dp(sz, 1);
        for (int i = 1; i < n; i++) {
            vector<int> ndp(sz);
            for (int u = 0; u < sz; u++) 
                for (int v : g[u]) add(ndp[u], dp[v]);
            swap(dp, ndp);
        }
        int ans = 0;
        for (int u = 0; u < sz; u++) add(ans, dp[u]);
        return ans;
    }
};