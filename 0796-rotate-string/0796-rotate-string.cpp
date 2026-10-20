#define ll long long
class Solution {
public:
    bool rotateString(string s, string goal) {
        if (s.size() != goal.size()) return false;
        ll a = 0, b = 0;
        int n = s.size(), m = goal.size();
        const ll base = 32;
        const int MOD = 1e9 + 7;
        ll mbase = 1;
        for (int i = 0; i < m; ++i) {
            b = base * b % MOD + (goal[i] - 'a' + 1);
            a = base * a % MOD + (s[i] - 'a' + 1);
            if (i > 0) mbase = mbase * base % MOD;
        }
        if (a == b) return true;
        for (int i = m; i < 2 * n; i++) {
            int l = (i - m) % n;
            a = (a - (s[l] - 'a' + 1) * mbase % MOD) % MOD;
            if (a < 0) a += MOD;
            a = (a * base % MOD + (s[i % n] - 'a' + 1));
            if (a == b) return true;
        }

        return false;
    }
};