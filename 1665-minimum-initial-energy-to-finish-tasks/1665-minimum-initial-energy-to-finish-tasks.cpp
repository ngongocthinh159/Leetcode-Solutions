// https://leetcode.com/problems/minimum-initial-energy-to-finish-tasks/solutions/8212664/why-sorted-by-difference-math-explain-by-cocl/?envType=daily-question&envId=2026-05-12
class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        int n = tasks.size();
        sort(tasks.begin(), tasks.end(), [](auto &a, auto &b) {
            return max(a[1], b[1] + a[0]) < max(b[1], a[1] + b[0]);
        });
        int cur = 0;
        int res = 0;
        for (int i = 0; i < n; i++) {
            int will = max(0, tasks[i][1] - cur);
            res += will;
            cur += will;
            cur -= tasks[i][0];
        }
        return res;
    }
};