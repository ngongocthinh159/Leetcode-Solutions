class Solution {
public:
    long long countPairs(vector<string>& words) {
        int n = words.size();
        unordered_map<string,int> f;
        for (auto &s : words) {
            string t = s;
            int dist = t[0] - 'a';
            for (int i = 0; i < t.size(); i++) {
                int x = t[i] - 'a';
                x = ((x - dist) % 26 + 26) % 26;
                t[i] = x + 'a';
            }
            s = t;
        }
        long long ans = 0;
        for (auto &s : words) f[s]++;
        for (auto &[s, cnt] : f) ans += 1ll * cnt * (cnt - 1) / 2;
        return ans;
    }
};