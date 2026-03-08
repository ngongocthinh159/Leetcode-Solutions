class Solution {
public:
    bool isSorted(const string &s) {
        int n = s.size();
        bool ok = true;
        for (int i = 1; i < n; i++) {
            if (s[i] < s[i - 1]) {
                return false;
            }
        }
        return true;
    }
    string sortRange(string s, const vector<vector<int>> &v) {
        for (auto &t : v) {
            sort(s.begin() + t[0], s.begin() + t[1] + 1);
        }
        return s;
    }
    int minOperations(string s) {
        int n = s.size();
        if (n == 2)
            return isSorted(s) ? 0 : -1;
        if (isSorted(s)) return 0;
        if (isSorted(sortRange(s, {{0, n - 2}})) || isSorted(sortRange(s, {{1, n - 1}}))) return 1;
        if (isSorted(sortRange(s, {{0, n - 2}, {1, n - 1}})) || 
            isSorted(sortRange(s, {{1, n - 1}, {0, n - 2}}))) return 2;
        return 3;
    }
};