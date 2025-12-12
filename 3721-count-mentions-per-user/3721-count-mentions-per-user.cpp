struct E {
    int time, type, id;
};
class Solution {
public:
    vector<int> split(string &s) {
        int i = 0, n = s.size();
        vector<int> res;
        while (i < n) {
            while (i < n && s[i] == ' ') i++;
            string cur = "";
            while (i < n && s[i] != ' ') cur += s[i++];
            cur = cur.substr(2);
            res.push_back(stoi(cur));
        }
        return res;
    }
    vector<int> countMentions(int n, vector<vector<string>>& events) {
        unordered_set<int> onl;
        for (int i = 0; i < n; i++) onl.insert(i);
        auto cmp = [&](auto &E1, auto &E2) {
            if (E2.time < E1.time) return true;
            if (E2.time == E1.time && E2.type < E1.type) return true;
            return false;
        };
        priority_queue<E,vector<E>,decltype(cmp)> q(cmp);
        for (int i = 0; i < events.size(); i++) {
            int time = stoi(events[i][1]);
            q.push(E{time, events[i][0] == "OFFLINE" ? 2 : 3, i});
        }
        vector<int> ans(n);
        while (q.size()) {
            auto _e = q.top(); q.pop();
            if (_e.type == 1) {
                onl.insert(_e.id);
            } else {
                auto &e = events[_e.id];
                int time = _e.time;
                if (_e.type == 2) {
                    int id = stoi(e[2]);
                    onl.erase(id);
                    q.push(E{time + 60, 1, id});
                } else {
                    if (e[2] == "ALL") {
                        for (int i = 0; i < n; i++) ans[i]++;
                    } else if (e[2] == "HERE") {
                        for (auto id : onl) ans[id]++;
                    } else {
                        auto ids = split(e[2]);
                        for (auto id : ids) ans[id]++;
                    }
                }
            }
        }
        return ans;
    }
};