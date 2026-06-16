class Solution {
public:
    int getNum(int &i, string &s) {
        int x = 0, cur = 1;
        while (i >= 0 && '0' <= s[i] && s[i] <= '9') {
            x += cur * (s[i] - '0');
            cur = cur * 10;
            i--;
        }
        return max(x, 1);
    }
    string getStr(int &i, string &s) {
        string t = "";
        while (i >= 0 && 'a' <= s[i] && s[i] <= 'z') t += s[i--];
        t += s[i--];
        reverse(t.begin(), t.end());
        return t;
    }
    string countOfAtoms(string s) {
        int n = s.size(), i = n - 1;
        map<string,int> f;
        int mul = 1;
        vector<int> st;
        while (i >= 0) {
            if (s[i] == '(') {
                mul /= st.back();
                st.pop_back();
                i--;
            } else {
                int num = getNum(i, s);

                if (s[i] == ')') {
                    mul = mul * num;
                    st.push_back(num);
                    i--;
                } else {
                    string t = getStr(i, s);
                    f[t] += num * mul;
                }
            }
        }
        string res = "";
        for (auto &[t, cnt] : f) {
            res += t;
            if (cnt > 1) res += to_string(cnt);
        }
        return res;
    }
};