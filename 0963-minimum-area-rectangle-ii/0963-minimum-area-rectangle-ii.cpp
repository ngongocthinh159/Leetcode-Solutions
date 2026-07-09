class Solution {
public:
    long long getCenter(vector<int> &a, vector<int> &b) {
        int x = a[0] + b[0];
        int y = a[1] + b[1];
        return x + 1ll * y * 1e8;
    }
    long long getLen(vector<int> &a, vector<int> &b) {
        return 1ll * (a[0] - b[0]) * (a[0] - b[0]) + 1ll * (a[1] - b[1]) * (a[1] - b[1]);
    }
    long long getLenVec(vector<int> &c) {
        return c[0] * c[0] + c[1] * c[1];
    }
    double minAreaFreeRect(vector<vector<int>>& points) {
        int n = points.size();
        double ans = 1e18;
        unordered_map<long long,unordered_map<long long,vector<array<int,2>>>> M;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                M[getCenter(points[i], points[j])][getLen(points[i], points[j])].push_back({i, j});
            }

        for (auto &[center, f] : M)
            for (auto &[len, list] : f) {
                int m = list.size();
                for (int i = 0; i < m; i++)
                    for (int j = i + 1; j < m; j++) {
                        auto [i1, j1] = list[i];
                        auto [i2, j2] = list[j];
                        vector<int> a = {points[i1][0] - points[i2][0], points[i1][1] - points[i2][1]};
                        vector<int> b = {points[i1][0] - points[j2][0], points[i1][1] - points[j2][1]};
                        double area = sqrt(getLenVec(a) * getLenVec(b));
                        ans = min(ans, area);
                    }
            }
        
        return ans == 1e18 ? 0 : ans;
    }
};