class Solution {
public:
    int scoreOfParentheses(string s) {
        int n = s.size();
        vector<int> st;
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') st.push_back(-1);
            else {
                int cur;
                if (st.back() != -1) {
                    cur = 2 * st.back();
                    st.pop_back();
                    st.pop_back();
                } else {
                    cur = 1;
                    st.pop_back();
                }
                if (st.size() && st.back() != -1) {
                    cur += st.back();
                    st.pop_back();
                }
                st.push_back(cur);
            }
        }
        return st[0];
    }
};