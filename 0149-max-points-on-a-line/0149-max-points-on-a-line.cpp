#define ll long long
class Solution {
public:
    array<ll, 2> find(vector<int>&p1, vector<int>&p2) {
        int x1 = p1[0], y1 = p1[1], x2 = p2[0], y2 = p2[1];
        ll a, b;
        if (x1 == x2) {
            return {LLONG_MAX, LLONG_MAX};
        } else {
            a = y2 - y1, b = x1 - x2;
            if (a < 0) a *= -1, b *= -1;
            ll g = gcd(abs(a), abs(b));
            a /= g; b /= g;
            return {a, b};
        }
    }
    int maxPoints(vector<vector<int>>& points) {
        // a * x1 + b * y1 + c = 0
        // a * x2 + b * y2 + c = 0
        // a * (x1 - x2) + b * (y1 - y2) = 0
        // a * (x1 - x2) = b * (y2 - y1)
        int n = points.size();
        int ans = 1;
        for (int i = 0; i < n; i++) {
            unordered_map<ll,unordered_map<ll,int>> f;
            for (int j = 0; j < n; j++) if (i != j) {
                auto [a, b] = find(points[i], points[j]);
                ans = max(ans, ++f[a][b] + 1);
            }
        }
        return ans;
    }
};