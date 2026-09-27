class Solution {
public:
    string reverseParentheses(string s) {
        int n = s.size();
        vector<char> st;
        for (int i = 0; i < n; i++) {
            if (s[i] == ')') {
                string t = "";
                while (st.size() && st.back() != '(') t += st.back(), st.pop_back();
                st.pop_back();
                for (int j = 0; j < int(t.size()); j++) st.push_back(t[j]);
            } else {
                st.push_back(s[i]);
            }
        }
        string res = "";
        for (int i = 0; i < int(st.size()); i++) res += st[i];
        return res;
    }
};