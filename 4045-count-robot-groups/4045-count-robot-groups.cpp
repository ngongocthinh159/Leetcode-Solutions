class Solution {
public:
    int countGroups(vector<int>& position, vector<int>& speed, int distance) {
        int n = position.size();
        vector<pair<int,int>> v;
        for (int i = 0; i < n; ) {
            while (i + 1 < n && ((position[i + 1] - position[i]) <= distance)) i++;
            v.push_back({position[i], speed[i]});
            i++;
        }
        int sz = v.size();
        // for (int i = 0; i < sz; i++) cout << v[i].second << ' ';
        // cout << '\n';
        // cout << sz << '\n';
        int cnt = 0;
        for (int i = sz - 1; i >= 0; ) {
            int cspeed = v[i].second;
            while (i - 1 >= 0 && (v[i - 1].second > cspeed)) i--;
            cnt++;
            i--;
        }
        return cnt;
    }
};