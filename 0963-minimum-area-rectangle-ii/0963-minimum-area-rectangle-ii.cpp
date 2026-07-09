class Solution {
public:
    bool isPerpendicular(vector<int> &a, vector<int> &b) {
        return (a[0] * b[0] + a[1] * b[1]) == 0;
    }
    double minAreaFreeRect(vector<vector<int>>& points) {
        int n = points.size();
        double ans = 1e18;
        unordered_map<int,unordered_map<int,bool>> vis;
        for (auto &p : points) vis[p[0]][p[1]] = 1;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++) if (i != j && i != k && j != k) {
                    vector<int> ki = {points[i][0] - points[k][0], points[i][1] - points[k][1]};
                    vector<int> kj = {points[j][0] - points[k][0], points[j][1] - points[k][1]};
                    if (isPerpendicular(ki, kj)) {
                        vector<int> c = {points[i][0] + points[j][0], points[i][1] + points[j][1]};
                        vector<int> delta = {2*points[k][0] - c[0], 2*points[k][1] - c[1]};
                        vector<int> r = {c[0] - delta[0], c[1] - delta[1]};
                        if (r[0] % 2 != 0 || r[1] % 2 != 0) continue;

                        r[0] /= 2;
                        r[1] /= 2;
                        
                        if (vis[r[0]][r[1]]) {
                            ans = min(ans, sqrt ( 1ll * (ki[0] * ki[0] + ki[1] * ki[1]) * (kj[0] * kj[0] + kj[1] * kj[1]) ));
                        }
                    }
                }
        return ans == 1e18 ? 0 : ans;
    }
};