struct rect {
    int t, b, l, r;
};
class Solution {
public:
    long long cal(const rect &r1, const rect &r2) {
        long long h = max(0, min(r1.t, r2.t) - max(r1.b, r2.b));
        long long w = max(0, min(r1.r, r2.r) - max(r1.l, r2.l));
        long long len = min(h, w);
        return len * len;
    }
    long long largestSquareArea(vector<vector<int>>& bottomLeft, vector<vector<int>>& topRight) {
        int n = bottomLeft.size();
        long long ans = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < i; j++) {
                ans = max(ans, cal(rect{topRight[i][1], bottomLeft[i][1], bottomLeft[i][0], topRight[i][0]},
                                    rect{topRight[j][1], bottomLeft[j][1], bottomLeft[j][0], topRight[j][0]}));
            }
        return ans;
    }
};