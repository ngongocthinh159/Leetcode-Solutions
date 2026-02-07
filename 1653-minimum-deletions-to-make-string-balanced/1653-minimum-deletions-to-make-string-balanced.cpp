class Solution {
public:
    const int IINF = 1e9 + 5;
    int minimumDeletions(string s) {
        int n = s.size();
        int p0 = 0, p1 = IINF;  
        for (int i = 1; i <= n; i++) {
            char c = s[i - 1] - 'a';
            int np0, np1;
            np0 = p0 + (c != 0);
            if (c == 0) np1 = p1 + 1;
            else np1 = min(p0, p1);
            swap(p0, np0);
            swap(p1, np1);
        }
        return min(p0, p1);
    }
};