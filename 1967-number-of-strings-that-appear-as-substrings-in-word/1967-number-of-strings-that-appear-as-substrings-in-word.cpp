class Solution {
public:
    int numOfStrings(vector<string>& patterns, string word) {
        int cnt = 0, n = word.size();
        for (auto p : patterns) 
            for (int i = 0; i < int(word.size()); i++) if (n - i >= p.size() && word.substr(i, p.size()) == p) {
                cnt++;
                break;
            }
        return cnt;
    }
};