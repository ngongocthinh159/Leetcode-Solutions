class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        int open = 0, pop = 0, close = 0, ans = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') open++;
            else {
                open--;
                pop++;
                if (open < 0) open = 0, pop = 0;
                else if (open == 0) {
                    ans = max(ans, 2 * pop);
                }
            }
        }
        pop = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == ')') close++;
            else {
                close--;
                pop++;
                if (close < 0) close = 0, pop = 0;
                else if (close == 0) {
                    ans = max(ans, 2 * pop);
                }
            }
        }
        return ans;
    }
};