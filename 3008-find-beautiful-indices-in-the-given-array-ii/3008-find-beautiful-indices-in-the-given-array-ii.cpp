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
    vector<int> beautifulIndices(string s, string a, string b, int k) {
        int n = s.size();
        string t = b + "#" + s;
        string u = a + "#" + s;
        auto z = z_function(t);
        auto zu = z_function(u);
        vector<int> lastB(n);
        vector<int> nextB(n);
        const int IINF = 1e6;
        for (int i = int(b.size()) + 1, j = 0; i < int(t.size()); ++i) {
            j = i - (int(b.size()) + 1);
            lastB[j] = (z[i] == int(b.size())) ? j : (j - 1 >= 0 ? lastB[j - 1] : -IINF);
        }
        for (int i = int(t.size()) - 1, j = 0; i >= int(b.size()) + 1; i--) {
            j = i - (int(b.size()) + 1);
            nextB[j] = (z[i] == int(b.size())) ? j : (j + 1 < n ? nextB[j + 1] : IINF);
        }
        vector<int> res;
        for (int i = int(a.size()) + 1; i < int(u.size()); i++) if (zu[i] == int(a.size())) {
            int j = i - (a.size() + 1);
            int mn = min(j - lastB[j], nextB[j] - j);
            if (mn <= k) res.push_back(j);
        }
        return res;
    }
};