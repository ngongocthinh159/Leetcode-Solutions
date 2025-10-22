struct Event {
    int x, type;
};
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        int n = nums.size();
        vector<Event> es;
        unordered_map<int,int> f;
        for (auto x : nums) {
            f[x]++;
            es.push_back(Event{x, 0});
            es.push_back(Event{x + k, 0});
            es.push_back(Event{x - k, 1});
            es.push_back(Event{x + k + 1, -1});
        }
        sort(es.begin(), es.end(), [](auto &e1, auto &e2) {
            if (e1.x < e2.x) return true;
            if (e1.x == e2.x && e1.type < e2.type) return true;
            return false;
        });
        int cnt = 0, ans = 0;
        for (auto &e : es) {
            if (e.type == -1) cnt--;
            if (e.type == 1) cnt++;
            ans = max(ans, min(cnt, numOperations + f[e.x]));
        }
        return ans;
    }
};