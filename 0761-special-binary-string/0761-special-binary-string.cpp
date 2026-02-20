class Solution {
public:
    string dfs(const string &s) {
        if (!s.size()) return "";
        
        int i = 0, n = s.size();
        vector<string> v;
        while (i < n) {
            int open = INT_MAX, st = i, end = i;
            while (i < n && (open != 0 || open == INT_MAX)) {
                end = i;
                if (open == INT_MAX) open = 0;
                if (s[i] == '1') open++;
                else open--;
                i++;
            }
            v.push_back("1" + dfs(s.substr(st + 1, end - st - 1)) + "0");
        }
        sort(v.begin(), v.end(), greater<>());
        string res = "";
        for (auto &str : v) res +=  str;
        return res;
    }
    string makeLargestSpecial(string s) {
        return dfs(s);
    }
};