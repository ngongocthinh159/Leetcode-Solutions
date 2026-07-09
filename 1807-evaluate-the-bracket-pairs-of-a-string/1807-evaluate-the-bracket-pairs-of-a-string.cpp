class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        int n = s.size();
        unordered_map<string,string> keyToValue;
        for (auto &p : knowledge) {
            keyToValue[p[0]] = p[1];
        }
        vector<char> st;
        for (int i = 0; i < n; i++) {
            if (s[i] != ')') st.push_back(s[i]);
            else {
                string cur = "";
                while (st.back() != '(') {
                    cur += st.back();
                    st.pop_back();
                }
                st.pop_back();
                reverse(cur.begin(), cur.end());
                if (keyToValue.count(cur)) {
                    cur = keyToValue[cur];
                    for (auto c : cur) st.push_back(c);
                } else {
                    st.push_back('?');
                }
            }   
        }
        string res = "";
        for (int i = 0; i < int(st.size()); i++) res += st[i];
        return res;
    }
};