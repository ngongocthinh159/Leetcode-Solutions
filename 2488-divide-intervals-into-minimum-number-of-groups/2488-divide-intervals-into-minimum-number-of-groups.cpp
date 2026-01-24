class Solution {
public:
    int minGroups(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<int> avail;
        int id = 0;
        priority_queue<array<int, 4>, vector<array<int, 4>>, greater<>> q;
        for (int i = 0; i < n; i++)
            q.push({intervals[i][0], 2, i, -1});
        while (q.size()) {
            auto [t, type, idx, g] = q.top();
            q.pop();
            if (type == 1) {
                avail.push_back(g);
            } else {
                int ug;
                if (avail.size())
                    ug = avail.back(), avail.pop_back();
                else
                    ug = id++;
                q.push({intervals[idx][1] + 1, 1, idx, ug});
            }
        }
        return id;
    }
};