class Solution {
public:
    int minAddToMakeValid(string s) {
        int n = s.size();
        int open = 0;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') open++;
            else {
                if (open) open--;
                else ans++;
            }
        }
        ans += open;
        return ans;
    }
};