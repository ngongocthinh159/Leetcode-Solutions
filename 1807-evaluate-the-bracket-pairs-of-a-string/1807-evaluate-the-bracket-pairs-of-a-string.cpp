class Solution {
public:
    int n;
    unordered_map<string,string> keyToValue;
    vector<int> toRight;
    string dfs(int l, int r, string &s, int inside) {
        string res = "";
        for (int i = l; i <= r; ) {
            if (s[i] == '(') {
                res += dfs(i + 1, toRight[i] - 1, s, 1);
                i = toRight[i] + 1;
            } else {
                res += s[i];
                i++;
            }
        }
        if (inside) {
            if (keyToValue.count(res)) 
                res = keyToValue[res];
            else 
                res = "?";
        }
        return res;
    }
    string evaluate(string s, vector<vector<string>>& knowledge) {
        n = s.size();
        for (auto &p : knowledge) {
            keyToValue[p[0]] = p[1];
        }
        vector<int> st;
        toRight.resize(n);
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') st.push_back(i);
            if (s[i] == ')') toRight[st.back()] = i, st.pop_back();
        }
        return dfs(0, n - 1, s, 0);
    }
};