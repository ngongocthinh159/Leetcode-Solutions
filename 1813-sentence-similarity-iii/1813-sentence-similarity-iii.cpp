class Solution {
public:
    vector<string> toToken(string &s1) {
        int n = s1.size();
        vector<string> token;
        for (int i = 0; i < n; ) {
            while (i < n && s1[i] == ' ') i++;
            string cur = "";
            while (i < n && s1[i] != ' ') cur += s1[i], i++;
            if (cur != "")
                token.push_back(cur);
        }
        return token;
    }
    bool areSentencesSimilar(string s1, string s2) {
        int n = s1.size();
        int m = s2.size();
        vector<string> token1 = toToken(s1);
        vector<string> token2 = toToken(s2);
        if (token1.size() > token2.size()) swap(token1, token2);
        int pref = 0, suf = 0;
        for (int i = 0; i < token1.size(); i++) {
            if (token1[i] == token2[i]) {
                pref++;
            } else
                break;
        }
        for (int i = int(token1.size()) - 1, j = int(token2.size()) - 1; i >= 0; i--, j--) {
            if (token1[i] == token2[j]) {
                suf++;
            } else
                break;
        }
        for (int i = -1; i < int(token1.size()); i++) {
            if (i + 1 <= pref && suf >= int(token1.size()) - pref) return true;
        }
        return false;
    }
};