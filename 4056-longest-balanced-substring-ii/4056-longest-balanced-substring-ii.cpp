class Solution {
public:
    int cal(string &s, char c1, char c2) {
        int n = s.size();
        int ans = 0;
        for (int j = 0; j < n;) {
            while (j < n && s[j] != c1 && s[j] != c2) j++;
            unordered_map<int,int> f;
            f[0] = j - 1;
            int cnt1 = 0, cnt2 = 0;
            while (j < n && (s[j] == c1 || s[j] == c2)) {
                if (s[j] == c1) cnt1++;
                else cnt2++;
                if (f.count(cnt1 - cnt2))
                    ans = max(ans, j - f[cnt1 - cnt2]);
                else
                    f[cnt1 - cnt2] = j;
                j++;
            }
        }
        return ans;
    }
    int longestBalanced(string s) {
        int n = s.size(), ans = 0, a = 0, b = 0, c = 0;
        unordered_map<int,unordered_map<int,int>> f;
        f[0][0] = -1;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'a') a++;
            else if (s[i] == 'b') b++;
            else c++;
            int d1 = a - b;
            int d2 = a - c;
            if (f.count(d1) && f[d1].count(d2))
                ans = max(ans, i - f[d1][d2]);
            else
                f[d1][d2] = i;
        }
        ans = max(ans, cal(s, 'a', 'b'));
        ans = max(ans, cal(s, 'a', 'c'));
        ans = max(ans, cal(s, 'b', 'c'));
        for (int i = 0; i < n;) {
            char c  =s[i];
            int cnt = 0;
            while (i < n && c == s[i]) {
                cnt++; i++;
            }
            ans = max(ans, cnt);
        }
        return ans;
    }
};