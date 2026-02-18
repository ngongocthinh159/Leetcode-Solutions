class Solution {
public:
    vector<bool> canMakePaliQueries(string s, vector<vector<int>>& queries) {
        int n = s.size();
        vector<int> pref(n + 1);
        for (int i= 0; i < n; i++) pref[i+ 1] = pref[i] ^ (1 << (s[i] - 'a'));
        vector<bool> ans;
        for (auto &q : queries) {
            int cur = pref[q[1] + 1] ^ pref[q[0]];
            int need = __builtin_popcount(cur)/2;
            if (need <= q[2]) ans.push_back(true);
            else ans.push_back(false);
        }
        return ans;
    }
};