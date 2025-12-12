class Solution {
public:
    int buf[3];
    const int base = 1e4;
    unordered_map<int,unordered_map<int,int>> f1;
        unordered_map<int,unordered_map<int,unordered_map<int,int>>> f2;
        unordered_map<int,int> f3;
        unordered_map<int,unordered_map<int,int>> f4;
    void find(vector<int> &p1, vector<int> &p2) {
        int a, b, c, g;
        if (p1[0] == p2[0]) {
            a = 1, b = 0, c = -p1[0];
        } else if (p1[1] == p2[1]) {
            a = 0, b = 1, c = -p1[1];
        } else {
            a = p2[1] - p1[1];
            b = p1[0] - p2[0];
            if (a < 0) a = -a, b = -b;
            g = gcd(abs(a), abs(b));
            a /= g; b /= g;
            c = -(a * p1[0] + b * p1[1]);
        }

        buf[0] = a, buf[1] = b, buf[2] = c;
    }
    int hash(const pair<int,int> &p) {
        return p.first + p.second * base;
    }
    int countTrapezoids(vector<vector<int>>& points) {
        int n = points.size();
        
        for (int i = 0; i < n; i++)
            for (int j = i - 1; j >= 0; j--) {
                find(points[i], points[j]);
                f1[buf[0]][buf[1]]++;
                f2[buf[0]][buf[1]][buf[2]]++;
                int mpoint = hash({points[i][0] + points[j][0], points[i][1] + points[j][1]});
                f3[mpoint]++;
                f4[mpoint][hash({buf[0], buf[1]})]++;
            }
        long long ans = 0;
        for (auto &[a, bToCnt] : f1) {
            for (auto &[b, cnt] : bToCnt) {
                ans += 1LL * cnt * (cnt - 1) / 2;
                for (auto &[c, cnt2] : f2[a][b])
                    ans -= 1LL * cnt2 * (cnt2 - 1) / 2;
            }
        }
        int para = 0;
        for (auto &[mpoint, cnt] : f3) {
            para += 1LL * cnt * (cnt - 1)/2;
            for (auto &[k, cnt2] : f4[mpoint]) {
                para -= 1LL * cnt2 * (cnt2 - 1) / 2;
            }
        }
        return ans - para;
    }
};