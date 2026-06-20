class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& r) {
        r.push_back({1, 0});
        int m = r.size();
        sort(r.begin(), r.end());
        int idx = 0;
        for (int i = 1; i < m; i++) {
            int dist = r[i][0] - r[idx][0];
            // new constraint
            if (r[i][1] <= r[idx][1] + dist) {
                idx = i;
            } else {
                r[i][1] = r[idx][1] + dist;
            }
        }
        idx = m - 1;
        for (int i = m - 2; i >= 0; i--) {
            int dist = r[idx][0] - r[i][0];
            // new constraint
            if (r[i][1] <= r[idx][1] + dist) {
                idx = i;
            } else {
                r[i][1] = r[idx][1] + dist;
            }
        }

        int ans = 0;
        for (int i = 1; i < int(r.size()); i++) {
            int lo = r[i - 1][1];
            int hi = r[i][1];
            int dist = r[i][0] - r[i - 1][0];
            if (lo > hi) swap(lo, hi);

            int remain = dist - (hi - lo);
            if (remain&1) remain--;

            ans = max(ans, hi + remain / 2);
        }
        ans = max(ans, n - r[m - 1][0] + r[m - 1][1]);
        return ans;
    }
};