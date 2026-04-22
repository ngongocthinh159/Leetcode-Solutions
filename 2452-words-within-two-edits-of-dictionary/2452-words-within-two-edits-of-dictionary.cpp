class Solution {
public:
    vector<string> twoEditWords(vector<string>& queries, vector<string>& dictionary) {
        int n = queries.size();
        vector<string> res;
        for (auto &s : queries) {
            for (auto &t : dictionary) {
                int cnt = 0;
                for (int i = 0; i < int(t.size()); i++) {
                    if (s[i] != t[i]) {
                        cnt++;
                        if (cnt >= 3) break;
                    }
                }
                if (cnt <= 2) {
                    res.push_back(s);
                    break;
                }
            }
        }
        return res;
    }
};