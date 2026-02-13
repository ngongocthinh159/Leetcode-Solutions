class Solution {
public:
    int longestBalanced(string s) {
        int n = s.size(), a = 0, b = 0, c = 0, ans = 0, win = 0, prev = -1; 
        unordered_map<int,unordered_map<int,int>> f;
        unordered_map<int,int> fab, fbc, fac;
        int aab = 0, bab = 0, bbc = 0, cbc = 0, aac = 0, cac = 0;
        f[0][0] = -1;
        fab[0] = fbc[0] = fac[0] = -1;
        for (int i = 0; i < n; i++) {
            if (prev == -1) prev = s[i];
            if (s[i] == prev) win++;
            else win = 1;
            prev = s[i];
            ans = max(ans, win);

            if (s[i] == 'a') {
                a++;
                bbc = cbc = 0;
                fbc = unordered_map<int,int>();
                fbc[0] = i;
                aab++, aac++;
            }
            else if (s[i] == 'b') {
                b++;
                aac = cac = 0;
                fac = unordered_map<int,int>();
                fac[0] = i;
                bab++, bbc++;
            }
            else {
                c++;
                aab = bab = 0;
                fab = unordered_map<int,int>();
                fab[0] = i;
                cbc++, cac++;
            }
            int x = a - b;
            int y = b - c;
            if (!f.count(x) || !f[x].count(y)) f[x][y] = i;
            else ans = max(ans, i - f[x][y]);

            x = aab - bab;
            if (!fab.count(x)) fab[x] = i;
            else ans = max(ans, i - fab[x]);
            x = bbc - cbc;
            if (!fbc.count(x)) fbc[x] = i;
            else ans = max(ans, i - fbc[x]);
            x = aac - cac;
            if (!fac.count(x)) fac[x] = i;
            else ans = max(ans, i - fac[x]);
        }
        return ans;
    }
};