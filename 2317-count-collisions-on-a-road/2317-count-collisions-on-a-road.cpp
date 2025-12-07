class Solution {
public:
    int countCollisions(string d) {
        int n = d.size();
        vector<int> ans(n);
        int R = 0, L = 0, S = 0;
        for (int i = 0; i < n; i++) {
            if (d[i] == 'L') {
                if (S != 0 || R != 0) ans[i] = 1;
            } else if (d[i] == 'R') {
                R++;
            } else {
                S++;
            }
        }
        R = 0,  L= 0, S = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (d[i] == 'R') {
                if (S != 0 || L != 0) ans[i] = 1;
            } else if (d[i] == 'L') {
                L++;
            } else {
                S++;
            }
        }
        int res = 0;
        for (auto x : ans) res += x;
        return res;
    }
};