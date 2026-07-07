class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        unordered_map<int,int> rtomnl;
        for (auto &i : intervals) {
            if (rtomnl.count(i[1]))
                rtomnl[i[1]] = min(rtomnl[i[1]], i[0]);
            else
                rtomnl[i[1]] = i[0];
        }
        int cnt = 0;
        sort(intervals.begin(), intervals.end(), [](auto &a, auto &b) {
            return a[1] < b[1];
        });
        int n = intervals.size();
        int mn = INT_MAX;
        for (int i = n - 1; i >= 0;) {
            int j = i;
            int r = intervals[i][1];
            while (j >= 0 && intervals[j][1] == r) {
                if (rtomnl[r] < intervals[j][0]) cnt++;
                else if (mn <= intervals[j][0]) {
                    cnt++;
                }
                j--;
            }
            while (i >= 0 && intervals[i][1] == r) {
                mn = min(mn, intervals[i][0]);
                i--;
            }
        }
        return n - cnt;
    }
};