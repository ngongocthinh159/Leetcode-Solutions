class Solution {
public:
    int minFlips(string s) {
        int n = s.size();
        if (n % 2 == 0) {
            return min(solve(s, 0), solve(s, 1));
        }
        return min(solve2(s, 0), solve2(s, 1));
    }
    int solve2(string &s, int c) {
        int n = s.size();
        int pref = 0, tot = 0, best = 0;
        for (int i = 0; i < n; i++) {
            int cur = s[i] - '0';
            int x ;
            if (cur ^ c) {
                tot++;
                pref++;
            } else
                pref--;

            best = max(best, pref);

            c ^= 1;
        }
        return max(0, tot - best);
    }
    int solve(string &s, int c) {
        int n = s.size();
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            int cur = s[i] - '0';
            if (cur ^ c) cnt++;
            c ^= 1;
        }
        return cnt;
    }
};