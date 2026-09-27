class Solution {
public:
    string reverseParentheses(string s) {
        int n = s.size();
        unordered_map<int,int> toIdx;
        vector<int> st;
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') st.push_back(i);
            if (s[i] == ')') {
                toIdx[st.back()] = i;
                toIdx[i] = st.back();
                st.pop_back();
            }
        }
        string res = "";
        for (int i = 0, dir = 1; i < n; i += dir) {
            if (s[i] == '(' || s[i] == ')') {
                i = toIdx[i];
                dir = -dir;
            } else {
                res += s[i];
            }
        }
        return res;
    }
};