class Solution {
public:
    void dfs(int remain, int open, vector<string> &res, string path) {
        if (remain == 0 && open == 0) {
            res.push_back(path);
            return;
        }
        if (remain) {
            path += '(';
            dfs(remain - 1, open + 1, res, path);
            path.pop_back();
        }
        if (open) {
            path += ')';
            dfs(remain, open - 1, res, path);
            path.pop_back();
        }
    }
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string path = "";
        dfs(n, 0, res, path);
        return res;
    }
};