struct event {
    int time, type, id;
};
class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<int> f(n,2);
        vector<event> es;
        for (int i = 0; i < n; i++)  { 
            auto &e = intervals[i];
            es.push_back(event{e[1] + 1, 1, i});
            es.push_back(event{e[0], 2, i});
            es.push_back(event{e[1], 3, i});
            es.push_back(event{e[1] - 1, 4, i});
        }
        sort(es.begin(), es.end(), [](auto &e1, auto &e2) {
            if (e1.time < e2.time) return true;
            if (e1.time == e2.time && e1.type < e2.type) return true;
            return false;
        });
        unordered_set<int> active;
        int ans = 0;
        for (int j = 0; j < es.size(); j++) {
            auto &e = es[j];
            int i = e.id;
            if (e.type == 1) {
                active.erase(i);
            } else if (e.type == 2) {
                active.insert(i);
            } else {
                if (e.type == 4 && f[i] <= 1) continue;
                if (f[i]) {
                    ans++;
                    for (auto idx : active)
                        if (f[idx]) f[idx]--;
                }
            }   
        }
        return ans;
    }
};