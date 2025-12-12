class Solution {
public:
    int buf[2];
    const int base = 1e4;
    unordered_map<int,unordered_map<int,int>> f1;
    unordered_map<int,unordered_map<int,int>> f2;
    void find(vector<int> &p1, vector<int> &p2) {
        int a, b, k, c, g;
        if (p1[0] == p2[0]) {
            k = 1, c = -p1[0];
        } else if (p1[1] == p2[1]) {
            k = base, c = -p1[1];
        } else {
            a = p2[1] - p1[1];
            b = p1[0] - p2[0];
            if (a < 0) a = -a, b = -b;
            g = gcd(abs(a), abs(b));
            a /= g; b /= g;
            k = a + base * b;
            c = -(a * p1[0] + b * p1[1]);
        }

        buf[0] = k, buf[1] = c;
    }
    int hash(const pair<int,int> &p) {
        return p.first + p.second * base;
    }
    int countTrapezoids(vector<vector<int>>& points) {
        int n = points.size();
        
        for (int i = 0; i < n; i++)
            for (int j = i - 1; j >= 0; j--) {
                find(points[i], points[j]);
                int slope = buf[0];
                f1[slope][buf[1]]++;
                int mpoint = hash({points[i][0] + points[j][0], points[i][1] + points[j][1]});
                f2[mpoint][slope]++;
            }
        int ans = 0;
        for (auto &[k, m] : f1) {
            int sum = 0;
            for (auto &[_, cnt] : m) {
                ans += cnt * sum;
                sum += cnt;
            }
        }
        int para = 0;
        for (auto &[mpoint, _f] : f2) {
            int sum = 0;
            for (auto &[_, cnt] : _f) {
                para += cnt * sum;
                sum += cnt;
            }
        }
        return ans - para;
    }
};