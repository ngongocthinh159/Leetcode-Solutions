class Solution {
public:
    int minInsertions(string s) {
        string t = "";
        int ans = 0;
        for (int i = 0; i < int(s.size()); ) {
            if (s[i] == '(') t += s[i++];
            else {
                int start = i, end = i;
                while (i < int(s.size()) && s[i] == ')') {
                    end = i;
                    i++;
                }
                if ((end - start + 1) & 1) end++, ans++;
                for (int j = start; j <= end; j += 2) t += ')';
            }
        }
        int n = t.size(), open = 0;
        for (auto c : t) {
            if (c == '(') open++;
            else {
                if (open) open--;
                else ans++;
            }
        }
        ans += 2 * open;
        return ans;
    }
};