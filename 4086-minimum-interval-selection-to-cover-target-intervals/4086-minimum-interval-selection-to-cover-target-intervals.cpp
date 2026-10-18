class Solution {
public:
    const int IINF = 1e9 + 7;
    int minSelection(vector<vector<int>>& availableIntervals, vector<vector<int>>& targetIntervals) {
        int n = availableIntervals.size();
        int m = targetIntervals.size();
        vector<vector<int>> v;
        sort(targetIntervals.begin(), targetIntervals.end());
        for (int i = 0; i < m; ) {
            auto cur = targetIntervals[i];
            while (i + 1 < m && isConnect(cur, targetIntervals[i + 1])) {
                cur = merge(cur, targetIntervals[i + 1]);
                i++;
            }
            v.push_back(cur);
            i++;
        }
        sort(availableIntervals.begin(), availableIntervals.end(), [](auto &x, auto &y) {
            return x[0] < y[0];
        });
        int sz = v.size();
        int x = v[0][0], ans = 0;
        for (int i = 0, j = 0; i < sz; ) {
            int mx = -1;
            while (j < n && availableIntervals[j][0] <= x) {
                mx = max(mx, availableIntervals[j][1]);
                j++;
            }
            if (mx < x) return -1;

            ans++;

            while (i < sz && v[i][1] <= mx) i++;
            if (i < sz) {
                x = max(v[i][0], mx);
            }
        }
        return ans;
    }
    bool isConnect(vector<int> &a, vector<int> &b) {
        if (a[0] > b[1] || b[0] > a[1]) return false;
        return true;
    }
    vector<int> merge(vector<int> &a, vector<int> &b) {
        return  {min(a[0], b[0]), max(a[1], b[1])};
    }
};