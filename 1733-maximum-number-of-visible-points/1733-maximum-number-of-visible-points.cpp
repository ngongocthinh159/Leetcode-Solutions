class Solution {
public:
    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        int x = location[0], y = location[1];
        vector<double> A;
        int same = 0;
        for (auto &p : points) {
            int X = p[0] - x;
            int Y = p[1] - y;
            if (X == 0 && Y == 0) {
                same++;
                continue;
            }
            double ang = atan2(Y, X) * (180.0 / M_PI);
            if (ang < 0) ang += 360;
            A.push_back(ang);
        }
        sort(A.begin(), A.end());
        vector<double> a = A;
        a.insert(a.end(), A.begin(), A.end());
        for (int i = A.size(); i < a.size(); i++) a[i] += 360;
        A = a;
        
        int n = A.size(), ans = 0;
        for (int r = 0, l = 0; r < n; r++) {
            while (l <= r && A[r] - A[l] > angle) l++;
            ans = max(ans, r - l + 1);
        }
        return ans + same;
    }
};