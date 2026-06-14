class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        vector<int> rightPos(n, -1);
        vector<int> st;
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') st.push_back(i);
            else {
                if (st.size()) rightPos[st.back()] = i, st.pop_back();
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ) {
            if (rightPos[i] == -1) {
                i++;
                continue;
            }
            int start = i, end = i;
            while (i < n) {
                if (rightPos[i] == -1) break;
                end = rightPos[i];
                i = rightPos[i] + 1;
            }
            ans = max(ans, end - start + 1);
        }
        return ans;
    }
};