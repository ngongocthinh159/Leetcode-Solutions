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
            auto e = q.top();
            time = e.time, type = e.type, mid = e.mid, rid = e.rid;
            q.pop();
            if (type == 1) {
                if (avail.size()) {
                    int used = *avail.begin();
                    avail.erase(avail.begin());
                    cnt[used]++;
                    q.push(event{meetings[mid][1], 2, mid, used});
                    // cout << "meeting " << mid << " used room " << used << "\n"; 
                } else {
                    delay.push_front(mid);
                    // cout << "meeting " << mid << " delayed " << "\n"; 
                }
                // cout << "\n";
            } else {
                // cout << "room " << rid << " become avail" << "\n";
                avail.insert(rid);
                while (q.size() && q.top().time == time && q.top().type == 2) {
                    avail.insert(q.top().rid);
                    q.pop();
                }
                while (delay.size() && avail.size()) {
                    int used = *avail.begin();
                    avail.erase(avail.begin());
                    int dmid = delay.back();
                    delay.pop_back();
                    cnt[used]++;
                    q.push({event{meetings[dmid][1] - meetings[dmid][0] + time, 2, dmid, used}});
                }
            }
        }
        int mx = -1, idx;
        for (int i = n - 1; i >= 0; i--) {
            if (mx <= cnt[i]) mx = cnt[i], idx = i;
        }
        return idx;
    }
};