class Solution {
public:
    double cal(double x, vector<vector<int>> &sq) {
        double sum = 0;
        for (auto &s : sq) sum += 1.00 * s[2] * (min(x, 1.00*s[1] + s[2]) - min(x, 1.00*s[1]));
        return sum;
    }
    double separateSquares(vector<vector<int>>& squares) {
        int n = squares.size();
        double tot = 0;
        for (auto &s : squares) tot+=1ll * s[2] * s[2];
        double l = 0, r = 1e9 + 5;
        for (int i = 0; i < 50; i++) {
            double m = l + (r - l)/2;
            if (2ll * cal(m, squares) < tot) l = m;
            else r = m;
        }
        return l;
    }
};