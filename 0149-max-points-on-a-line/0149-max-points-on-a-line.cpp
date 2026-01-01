#define ll long long
class Solution {
public:
    array<ll, 3> find(vector<int>&p1, vector<int>&p2) {
        int x1 = p1[0], y1 = p1[1], x2 = p2[0], y2 = p2[1];
        ll a, b, c;
        if (x1 == x2) {
            a = 1, b = 0;
        } else if (y1 == y2) {
            a = 0, b = 1;
        } else {
            a = y2 - y1, b = x1 - x2;
            if (a < 0) a *= -1, b *= -1;
            ll g = gcd(abs(a), abs(b));
            a /= g; b /= g;
        }
        c = - 1ll * a * x1 - 1ll * b * y1;
        return {a, b, c};
    }
    int maxPoints(vector<vector<int>>& points) {
        // a * x1 + b * y1 + c = 0
        // a * x2 + b * y2 + c = 0
        // a * (x1 - x2) + b * (y1 - y2) = 0
        // a * (x1 - x2) = b * (y2 - y1)
        int n = points.size();
        unordered_map<ll,unordered_map<ll,unordered_map<ll,int>>> f;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            set<array<ll, 3>> S;
            for (int j = 0; j < n; j++) if (i != j) {
                auto [a, b, c] = find(points[i], points[j]);
                if (!S.count({a, b ,c})) {
                    S.insert({a, b, c});
                    ans = max(ans, ++f[a][b][c]);
                }
            }
        }
        return ans;
    }
};