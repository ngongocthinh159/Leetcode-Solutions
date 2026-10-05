class Solution {
public:
    vector<int> toRight;
    int dfs(int l, int r) {
        if (l + 1 == r) return 1;
        if (toRight[l] == r) return 2 * dfs(l + 1, r - 1);
        int res = 0;
        for (int i = l; i <= r; ) {
            res += dfs(i, toRight[i]);
            i = toRight[i] + 1;
        }
        return res;
    }
    int scoreOfParentheses(string s) {
        int n = s.size();
        toRight.resize(n);
        vector<int> st;
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') st.push_back(i);
            else {
                toRight[st.back()] = i;
                st.pop_back();
            }
        }
        return dfs(0, n - 1);
    }
};