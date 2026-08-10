pair<int,int> dp[55][55][55][21][3];
class Solution {
public:
    void relax(pair<int,int> &a, pair<int,int> b) {
        if (a.first < b.first) a = b;
        else if (a.first == b.first) {
            a.second = min(a.second, b.second);
        }
    }
    pair<int,int> dfs(int i, int f0, int f1, int wait, int state, vector<int> &demand) {
        if (i == int(demand.size())) return {0, 0};
        if (dp[i][f0][f1][wait][state].first != -2) return dp[i][f0][f1][wait][state];

        int xwait;
        if (state == 0) xwait = 0;
        else if (state == 1) xwait = demand[i - 1];
        else xwait = demand[i - 1] - wait;

        pair<int,int> res = {-1,INT_MAX};
        int x = demand[i];
        if (f0 - wait >= x) {
            relax(res, {1, wait + xwait});

            auto tmp = dfs(i + 1, f0 - wait, f1, x, 0, demand);
            if (tmp.first != -1)
                relax(res, {1 + tmp.first, max(wait + xwait,tmp.second)});
        }
        if (f1 >= x) {
            relax(res, {1, xwait});

            int take = min(wait, x);
            int nf0, nf1, nwait, nstate;
            if (wait >= x) {
                nf0 = f0 - take;
                nf1 = f1 - take;
                nwait = wait - x;
                nstate = 1;
            } else {
                nf0 = f1 - take;
                nf1 = f0 - take;
                nwait = x - wait;
                nstate = 2;
            }
            auto tmp = dfs(i + 1, nf0, nf1, nwait, nstate, demand);
            if (tmp.first != -1) {
                relax(res, {1 + tmp.first, max(xwait, tmp.second)});
            }
        }

        return dp[i][f0][f1][wait][state] = res;
    }
    int minMaxWaitingTime(vector<int>& demand, vector<int>& fuel) {
        int n = demand.size();
        int mx = max(fuel[0], fuel[1]);
        int mxD = *max_element(demand.begin(), demand.end());
        for (int i = 0; i < n; i++)
            for (int j = 0; j <= mx; j++)
                for (int k = 0; k <= mx; k++)
                    for (int wait = 0; wait <= mxD; wait++)
                        for (int state = 0; state < 3; state++)
                            dp[i][j][k][wait][state] = {-2,-2};
        auto res =  dfs(0, fuel[0], fuel[1], 0, 0, demand);
        if (res.first == -1) return -1;
        return res.second;
    }
};