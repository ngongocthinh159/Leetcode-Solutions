class Solution {
public:
    void dfs(int i, string &s, int remove, int open, set<string> &S, string &cur) {
        if (i == s.size()) {
            if (open == 0 && remove == 0) S.insert(cur);
            return;
        }
        
        if (s[i] != '(' && s[i] != ')') {
            cur += s[i];
            dfs(i + 1, s, remove, open, S, cur);
            cur.pop_back();
            return;
        }

        // remove
        if (remove) dfs(i + 1, s, remove - 1, open, S, cur);

        // not remove
        if (s[i] == ')') {
            if (open > 0) {
                cur += s[i];
                dfs(i + 1, s, remove, open - 1, S, cur);
                cur.pop_back();
            }
        } else {
            cur += s[i];
            dfs(i + 1, s, remove, open + 1, S, cur);
            cur.pop_back();
        }
    }
    vector<string> removeInvalidParentheses(string s) {
        int n = s.size();
        int open = 0, match = 0, az = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] != '(' && s[i] != ')') {
                az++;
                continue;
            }
            if (s[i] == '(') open++;
            else {
                if (open > 0) {
                    open--;
                    match++;
                }
            }
        }
        int remove = n - 2*match - az; 
        cout << remove << '\n';
        set<string> S;
        string cur = "";
        dfs(0, s, remove, 0, S, cur);
        return vector<string>(S.begin(), S.end());
    }
};