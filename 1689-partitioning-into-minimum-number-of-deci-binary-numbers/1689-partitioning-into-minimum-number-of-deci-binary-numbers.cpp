class Solution {
public:
    int minPartitions(string s) {
        int n = s.size(), mx = -1;
        for (auto c : s) mx = max(mx, c - '0');
        return mx;
    }
};