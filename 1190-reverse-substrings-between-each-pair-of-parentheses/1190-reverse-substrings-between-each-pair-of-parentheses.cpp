class Solution {
public:
    int n;
    vector<int> toRight;
    string dfs(int l, int r, bool rev, string &s) {
        string res = "";
        for (int i = l; i <= r; ) {
            if (s[i] == '(') {
                res += dfs(i + 1, toRight[i] - 1, 1, s);
                i = toRight[i] + 1;
            } else {
                res += s[i];
                i++;
            }
        }
        if (rev) reverse(res.begin(), res.end());
        return res;
    }
    string reverseParentheses(string s) {
        n = s.size();
        toRight.resize(n);
        vector<int> st;
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') st.push_back(i);
            if (s[i] == ')') toRight[st.back()] = i, st.pop_back();
        }
        return dfs(0, n - 1, 0, s);
    }
};