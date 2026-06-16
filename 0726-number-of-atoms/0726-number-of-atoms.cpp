class Solution {
public:
    unordered_map<string,int> dfs(int L, int R, string &s, vector<int> &right) {
        unordered_map<string,int> f;
        for (int i = L; i <= R;) {
            if (s[i] == '(') {
                auto f2 = dfs(i + 1, right[i] - 1, s, right);
                i = right[i] + 1;
                int mul = 0;
                while (i <= R && '0' <= s[i] && s[i] <= '9') {
                    mul = mul * 10 + s[i] - '0';
                    i++;
                }
                mul = max(mul, 1);
                for (auto [c, cnt] : f2) {
                    f[c] += cnt * mul;
                }
            } else {
                string t = "";
                t += s[i];
                i++;
                while (i <= R && 'a' <= s[i] && s[i] <= 'z') {
                    t += s[i];
                    i++;
                }
                int cur = 0;
                while (i <= R && '0' <= s[i] && s[i] <= '9') {
                    cur = cur * 10 + s[i] - '0';
                    i++;
                }
                cur = max(cur, 1);
                f[t] += cur;
            }
        }
        return f;
    }
    string countOfAtoms(string s) {
        int n = s.size();
        vector<int> right(n);
        vector<int> st;
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') st.push_back(i);
            else if (s[i] == ')') {
                right[st.back()] = i;
                st.pop_back();
            }
        }
        auto f = dfs(0, n - 1, s, right);
        vector<pair<string,int>> v;
        for (auto &[t, cnt] : f) v.push_back({t, cnt});
        sort(v.begin(), v.end(), [&](auto &a, auto &b) {return a.first < b.first;});
        string res = "";
        for (auto &[t, cnt] : v) {
            res += t;
            if (cnt > 1) res += to_string(cnt);
        }
        return res;
    }
};