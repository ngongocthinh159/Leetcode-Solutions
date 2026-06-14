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
            int j = i, start = j, end = j;
            while (j < n) {
                if (rightPos[j] == -1) break;
                end = rightPos[j];
                j = rightPos[j] + 1;
            }
            ans = max(ans, end - start + 1);
            i = j;
        }
        return ans;
    }
};