class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        vector<int> st;
        vector<int> toRight(n, -1);
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') st.push_back(i);
            else {
                if (st.size()) {
                    toRight[st.back()] = i;
                    st.pop_back();
                } else
                    st.clear();
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ) {
            if (toRight[i] == -1) {
                i++;
                continue;
            }
            int len = 0;
            while (i < n && toRight[i] != -1) {
                len += toRight[i] - i + 1;
                i = toRight[i] + 1;
            }
            ans = max(ans, len);
        }
        return ans;
    }
};