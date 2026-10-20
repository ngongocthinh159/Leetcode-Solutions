class Solution {
public:
    vector<int> z_function(string s) {
        int n = s.size();
        vector<int> z(n);
        for(int i = 1, l = 0, r = 0 ; i < n; i++) {
            if(i <= r) {
                z[i] = min(r - i + 1, z[i - l]);
            }
            while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
                z[i]++;
            }
            if(i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }
        return z;
    }
    bool rotateString(string s, string goal) {
        if (s.size() != goal.size()) return false;
        string t = goal + "#" + s + s;
        auto z = z_function(t);
        for (int i = 0; i < int(t.size()); ++i) if (z[i] == int(goal.size())) return true;
        return false;
    }
};