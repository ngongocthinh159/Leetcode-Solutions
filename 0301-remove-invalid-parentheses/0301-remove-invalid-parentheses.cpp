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
        vector<string> res;
        string path = "";
        set<string> S;
        dfs(0, 0, remove, s, res, path, S);
        return res;
    }
    void dfs(int i, int open, int remove, string &s, vector<string> &res, string &path, set<string> &S) {
        if (remove > int(s.size()) - i) return;
        if (i == int(s.size())) {
            if (open != 0) return;
            if (!S.count(path)) {
                S.insert(path);
                res.push_back(path);
            }
            return;
        }

        if ('a' <= s[i] && s[i] <= 'z') {
            path += s[i];
            dfs(i + 1, open, remove, s, res, path, S);
            path.pop_back();
            return;
        }

        if (remove) {
            dfs(i + 1, open, remove - 1, s, res, path, S);
        }

        if (s[i] == '(') {
            path += s[i];
            dfs(i + 1, open + 1, remove, s, res, path, S);
            path.pop_back();
        } else if (s[i] == ')' && open > 0) {
            path += s[i];
            dfs(i + 1, open - 1, remove, s, res, path, S);
            path.pop_back();
        }
    }
};