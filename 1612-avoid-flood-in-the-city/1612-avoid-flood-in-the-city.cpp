class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        set<int> pos;
        int n = rains.size();
        unordered_map<int,int> f;
        vector<int> ans(n, -1);
        for (int i = 0; i < n; i++) {
            if (!rains[i]) {
                pos.insert(i);
            }
            else {
                if (f.count(rains[i])) {
                    int idx = f[rains[i]];
                    auto it = pos.lower_bound(idx);
                    if (it == pos.end())
                        return {};
                    ans[*it] = rains[i];
                    pos.erase(it);
                    f[rains[i]] = i;
                } else
                    f[rains[i]] = i;
            }
        }
        for (auto idx : pos) ans[idx] = 1;
        return ans;
    }
};