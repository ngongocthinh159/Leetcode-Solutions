class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        int n = s.size();
        int open = 0;
        int remove = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') open++;
            else if (s[i] == ')') {
                if (open == 0) {
                    remove++;
                } else {
                    open--;
                }
            }
        }
        remove += open;
        string path = "";
        unordered_set<string> S;
        dfs(0, 0, remove, s, path, S);
        return vector<string>(S.begin(), S.end());
    }
    void dfs(int i, int open, int remove, string &s, string &path, unordered_set<string> &S) {
        if (remove > int(s.size()) - i) return;
        if (i == int(s.size())) {
            if (open != 0) return;
            if (!S.count(path)) {
                S.insert(path);
            }
            return;
        }

        if ('a' <= s[i] && s[i] <= 'z') {
            path += s[i];
            dfs(i + 1, open, remove, s, path, S);
            path.pop_back();
            return;
        }

        if (remove) {
            dfs(i + 1, open, remove - 1, s, path, S);
        }

        if (s[i] == '(') {
            path += s[i];
            dfs(i + 1, open + 1, remove, s, path, S);
            path.pop_back();
        } else if (s[i] == ')' && open > 0) {
            path += s[i];
            dfs(i + 1, open - 1, remove, s, path, S);
            path.pop_back();
        }
    }
};