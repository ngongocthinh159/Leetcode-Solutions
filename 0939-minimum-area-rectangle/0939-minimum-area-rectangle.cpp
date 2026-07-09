class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        int n = points.size();
        unordered_map<int,unordered_map<int,bool>> vis;
        for (auto &p : points) vis[p[0]][p[1]] = 1;
        int ans = INT_MAX;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) if (j != i && points[j][0] > points[i][0] && points[j][1] < points[i][1]) {
                if (vis[points[j][0]][points[i][1]] && vis[points[i][0]][points[j][1]]) {
                    int area = (points[j][0] - points[i][0]) * (points[i][1] - points[j][1]);
                    ans = min(ans, area);
                }
            }
        return ans == INT_MAX ? 0 : ans;
    }
};