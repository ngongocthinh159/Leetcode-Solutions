class Solution {
public:
    vector<int> makePref(string &s, char x) {
        vector<int> pref(s.size() + 1);
        for (int i = 0; i < s.size(); i++) {
            pref[i + 1] = pref[i] + (x == s[i]);
        }
        return pref;
    }
    int distinctPoints(string s, int k) {
        auto prefU = makePref(s, 'U');
        auto prefD = makePref(s, 'D');
        auto prefL = makePref(s, 'L');
        auto prefR = makePref(s, 'R');
        int U = 0, D = 0, L = 0, R = 0;
        for (auto c : s) {
            if (c == 'U') U++;
            if (c == 'D') D++;
            if (c == 'L') L++;
            if (c == 'R') R++;
        }
        unordered_set<long long> S;
        long long base = 1e5 + 5;
        int n = s.size();
        for (int r = k - 1; r < n; r++) {
            int _u = U - (prefU[r + 1] - prefU[r - k + 1]);
            int _d = D - (prefD[r + 1] - prefD[r - k + 1]);
            int _l = L - (prefL[r + 1] - prefL[r - k + 1]);
            int _r = R - (prefR[r + 1] - prefR[r - k + 1]);
            int x = _r - _l;
            int y = _u - _d;
            S.insert(x + base * y);
        }
        return S.size();
    }
};