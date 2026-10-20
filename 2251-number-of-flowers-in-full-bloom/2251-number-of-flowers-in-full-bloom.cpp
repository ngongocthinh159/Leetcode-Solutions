class Solution {
public:
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people) {
        priority_queue<array<int,3>> q;
        int n = flowers.size(), m = people.size();
        for (int i = 0; i < n; ++i) {
            q.push({-flowers[i][0], 1, 0});
            q.push({-(flowers[i][1] + 1), 2, 0});
        }
        for (int i = 0; i < m; ++i) {
            q.push({-people[i], -1, i});
        }
        vector<int> ans(m);
        int cnt = 0;
        while (q.size()) {
            auto [time, type, idx] = q.top();
            if (type == 1) {
                cnt++;
            } else if (type == 2) {
                cnt--;
            } else {
                ans[idx] = cnt;
            }
            q.pop();
        }
        return ans;
    }
};