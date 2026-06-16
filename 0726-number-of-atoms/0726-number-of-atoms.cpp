class Solution {
public:
    int getNum(int &i, string &s) {
        int x = 0, n = s.size();
        while (i < n && '0' <= s[i] && s[i] <= '9') x = x * 10 + s[i++] - '0';
        return max(x, 1);
    }
    string getStr(int &i, string &s) {
        int n = s.size();
        string t = "";
        t += s[i++];
        while (i < n && 'a' <= s[i] && s[i] <= 'z') t += s[i++];
        return t;
    }
    string countOfAtoms(string s) {
        int n = s.size(), i = 0;
        vector<map<string,int>> st;
        st.push_back(map<string,int>());
        while (i < n) {
            if (s[i] == '(') {
                st.push_back(map<string,int>());
                i++;
            } else if (s[i] == ')') {
                i++;
                int mul = getNum(i, s);

                // merge
                if (st.size() > 1) {
                    auto &f2 = st[st.size() - 1];
                    auto &f = st[st.size() - 2];
                    for (auto &[t, cnt] : f2) f[t] += cnt * mul;
                    st.pop_back();
                }
            } else {
                string t = getStr(i, s);
                int mul = getNum(i, s);
                auto &f = st.back();
                f[t] += mul;
            }
        }
        string res = "";
        for (auto &[t, cnt] : st[0]) {
            res += t;
            if (cnt > 1) res += to_string(cnt);
        }
        return res;
    }
};