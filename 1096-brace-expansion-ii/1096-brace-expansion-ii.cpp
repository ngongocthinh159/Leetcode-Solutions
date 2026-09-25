class Solution {
public:
    int n;
    vector<int> toRight;
    void concatStr(int i, vector<vector<string>> &v, vector<string> &res, string &path) {
        if (i == v.size()) {
            res.push_back(path);
            return;
        }
        for (auto s : v[i]) {
            path += s;
            concatStr(i + 1, v, res, path);
            int cnt = s.size();
            while (cnt--) path.pop_back();
        }
    }
    vector<string> unionStr(vector<vector<string>> &v) {
        set<string> res;
        for (auto &list : v) 
            for (auto &s : list) res.insert(s);
        return vector<string>(res.begin(), res.end());
    }
    vector<string> dfs(int l, int r, string &s) {
        vector<vector<string>> toUnion;
        for (int i = l; i <= r; ) {
            vector<vector<string>> toConcat;
            while (i <= r && s[i] != ',') {
                if ('a' <= s[i] && s[i] <= 'z') {
                    string t = ""; t += s[i];
                    toConcat.push_back({t});
                    i++;
                } else if (s[i] == '{') {
                    toConcat.push_back(dfs(i + 1, toRight[i] - 1, s));
                    i = toRight[i] + 1;
                }
            }
            string path = "";
            vector<string> tmp;
            concatStr(0, toConcat, tmp, path);
            toUnion.push_back(tmp);
            i++;
        }
        return unionStr(toUnion);
    }
    vector<string> braceExpansionII(string s) {
        n = s.size();
        toRight.resize(n);
        vector<int> v;
        for (int i = 0; i < n; i++) {
            if (s[i] == '{') v.push_back(i);
            if (s[i] == '}') toRight[v.back()] = i, v.pop_back();
        }
        return dfs(0, n - 1, s);
    }
};