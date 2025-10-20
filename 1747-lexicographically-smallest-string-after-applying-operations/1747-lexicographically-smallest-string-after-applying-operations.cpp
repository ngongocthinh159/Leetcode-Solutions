class Solution {
public:
    vector<char> mm;
    void shift(string &s, int x) {
        if (x == 0) return;
        reverse(s.begin(), s.end() - x);
        reverse(s.end() - x, s.end());
        reverse(s.begin(), s.end());
    }
    void reduce(string &s, int idx) {
        int delta = ((mm[s[idx] - '0'] - s[idx]) + 10) % 10;
        for (int i = idx; i < s.size(); i += 2) {
            s[i] -= '0';
            s[i] += delta;
            s[i] %= 10;
            s[i] += '0';
        }
    }
    string findLexSmallestString(string s, int a, int b) {
        int n = s.size();
        vector<bool> vis(n);
        mm.assign(10, 255);
        for (int i = 0; i < 10; i++) {
            vector<bool> v(10);
            int mn = 10, cur = i;
            while (!v[cur]) {
                v[cur] = 1;
                mn = min(mn, cur);
                cur += a;
                cur %= 10;
            }
            mm[i] = mn + '0';
        }
        string mn = "";
        mn += '9' + 1;
        int cshift = 0;
        while (!vis[cshift]) {
            vis[cshift] = 1;
            string t = s;
            shift(t, cshift);
            reduce(t, 1);
            if (b & 1) reduce(t, 0);
            mn = min(mn, t);
            cshift += b;
            cshift %= n;
        } 
        return mn;
    }
};