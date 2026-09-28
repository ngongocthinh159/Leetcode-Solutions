class Solution {
public:
    int maxDepth(string s) {
        int ans = 0;
        int open = 0;
        for (auto c : s) {
            if (c == '(') open++;
            if (c == ')') open--;
            ans = max(ans, open);
        }
        return ans;
    }
};