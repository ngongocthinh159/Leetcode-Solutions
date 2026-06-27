class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long,int> f;
        for (auto x : nums) f[x]++;
        unordered_set<int> vis;
        int ans = 0;
        for (auto x : nums) if (!vis.count(x)) {
            vis.insert(x);
            int cnt = 0;
            long long cur = x;
            if (cur == 1) {
                continue;
            }
            while (f[cur] >= 2 && f[cur * cur] >= 1) {
                cnt++;
                cur = cur * cur;
            }
            ans = max(ans, 2*cnt + 1);
        }
        return max(ans, (f[1]&1) ? (f[1]) : (f[1] - 1));
    }
};