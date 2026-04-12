class Solution {
public:
    int longestBalanced(string s) {
        int n = s.size();
        unordered_map<int,vector<int>> M;
        int o = 0, z = 0;
        M[0].push_back(-1);
        int ans = 0;
        vector<int> p1(n), s1(n), p0(n), s0(n);
        for (int i = 0; i < n; i++) {
            p1[i] = (i > 0 ? p1[i - 1] : 0) | (s[i] == '1');
            p0[i] = (i > 0 ? p0[i - 1] : 0) | (s[i] == '0');
        }
        for (int i = n - 1; i >= 0; i--) {
            s1[i] = (i + 1 < n ? s1[i + 1] : 0) | (s[i] == '1');
            s0[i] = (i + 1 < n ? s0[i + 1] : 0) | (s[i] == '0');
        }
        for (int i = 0; i < n; i++) {
            if (s[i] == '1') o++;
            else z++;
            int delta = o - z;
            if (M.count(delta)) {
                ans = max(ans, i - M[delta][0]);
            }
            int toTry[2] = {delta - 2, delta + 2};
            for (int j = 0; j < 2; j++) {
                int curDelta = toTry[j];
                if (M.count(curDelta)) {
                    int idx = M[curDelta][0];
                    int need = j == 0 ? 0 : 1;
                    auto &p = need == 1 ? p1 : p0;
                    auto &s = need == 1 ? s1 : s0;
                    if ((idx >= 0 && p[idx]) || (i + 1 < n && s[i + 1]))  {
                        ans = max(ans, i - idx);
                    }
                    if (M[curDelta].size() >= 2) {
                        int idx2 = M[curDelta][1];
                        ans = max(ans, i - idx2);
                    }
                }
            }

            M[delta].push_back(i);
        }
        return ans;
    }
};