class Solution {
public:
    string maximumXor(string s, string t) {
        int n = s.size();
        int cnt[2]{};
        for (auto  c  :t) cnt[c - '0']++;
        string res = s;
        for (int i = 0; i < n; i++) {
            int idx = s[i] - '0';
            int desired = idx ^ 1;
            if (cnt[desired]) {
                cnt[desired]--;
                res[i] = '1';
            } else {
                cnt[idx]--;
                res[i] = '0';
            }
        }
        return res;
    }
};