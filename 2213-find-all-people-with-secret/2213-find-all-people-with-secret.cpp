class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        set<pair<int,int>> S;
        unordered_set<int> vis;
        unordered_map<int,vector<pair<int,int>>> g;
        for (auto &m : meetings) {
            g[m[0]].push_back({m[1], m[2]});
            g[m[1]].push_back({m[0], m[2]});
        }
        S.insert({0, firstPerson});
        for (auto [v, time] : g[0]) S.insert({time, v});
        vis.insert(0);
        while (S.size()) {
            auto [time, u] = *S.begin();
            S.erase(S.begin());
            if (vis.count(u)) continue;
            vis.insert(u);
            for (auto [v, time_uv] : g[u]) if (!vis.count(v) && time <= time_uv) {
                S.insert({time_uv, v});
            }
        }
        vector<int> res(vis.begin(), vis.end());
        return res;
    }
};