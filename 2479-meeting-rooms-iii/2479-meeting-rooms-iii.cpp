struct event {
    long long time, type, mid, rid;
};
class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        int m = meetings.size();
        set<int> avail;
        for (int i = 0; i < n; i++) avail.insert(i);
        deque<int> delay;
        auto cmp = [](auto &e1, auto &e2) {
            if (e2.time < e1.time) return true;
            if (e2.time == e1.time && e2.type > e1.type) return true;
            return false; 
        };
        priority_queue<event,vector<event>,decltype(cmp)> q;
        for (int i = 0; i < m; i++) {
            auto &m = meetings[i];
            q.push(event{m[0], 1, i, -1});
        }
        long long time, type, mid, rid;
        vector<int> cnt(n);
        while(q.size()) {
            long long ctime = q.top().time;

            while (q.size() && q.top().time == ctime && q.top().type == 2) {
                avail.insert(q.top().rid);
                q.pop();
            }

            while (delay.size() && avail.size()) {
                int ridused = *avail.begin();
                avail.erase(avail.begin());
                int midused = delay.back();
                delay.pop_back();
                cnt[ridused]++;
                q.push(event{ctime - meetings[midused][0] + meetings[midused][1], 2, midused, ridused});
            }

            while (q.size() && q.top().time == ctime && q.top().type == 1) {
                auto &e = q.top();
                time = e.time, type = e.type, mid = e.mid, rid = e.rid;
                if (avail.empty()) {
                    delay.push_front(mid);
                } else {
                    int ridused = *avail.begin();
                    avail.erase(avail.begin());
                    cnt[ridused]++;
                    q.push(event{meetings[mid][1], 2, mid, ridused});
                }

                q.pop();
            }
        }
        int mx = -1, idx;
        for (int i = n - 1; i >= 0; i--) {
            if (mx <= cnt[i]) mx = cnt[i], idx = i;
        }
        return idx;
    }
};