class Solution {
public:
    double EPS = 1e-7;
    int cnt(vector<vector<int>> &d, vector<double> &c, int r) {
        int n = d.size();
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if ((c[0] - d[i][0]) * (c[0] - d[i][0]) + (c[1] - d[i][1]) * (c[1] - d[i][1]) <= r * r + EPS) cnt++;
        }
        return cnt;
    }
    int numPoints(vector<vector<int>>& d, int r) {
        int n = d.size();
        int ans = 1;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                vector<double> c = {1.00 * (d[i][0] + d[j][0]) / 2, 1.00 * (d[i][1] + d[j][1]) / 2};
                vector<double> dirV = {(double) d[j][0] - d[i][0], (double) d[j][1] - d[i][1]};
                double dist = dirV[0] * dirV[0] + dirV[1] * dirV[1];
                // cout << dist << '\n';
                if (dist > 4 * r * r) continue;
                vector<double> normV = {-dirV[1], dirV[0]};
                double normLen = sqrt(normV[0] * normV[0] + normV[1] * normV[1]);
                normV[0] /= normLen;
                normV[1] /= normLen;
                double X = sqrt(1.00 * r * r - 1.00 * dist / 4);
                vector<double> r1 = {c[0] + X * normV[0], c[1] + X * normV[1]};
                vector<double> r2 = {c[0] - X * normV[0], c[1] - X * normV[1]};
                ans = max(ans, cnt(d, r1, r));
                ans = max(ans, cnt(d, r2, r));
            }
        return ans;
    }
};