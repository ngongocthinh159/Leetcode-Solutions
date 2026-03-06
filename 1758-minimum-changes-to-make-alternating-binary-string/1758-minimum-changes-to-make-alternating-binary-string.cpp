class Solution {
public:
    int minOperations(string s) {
        int cnt1 = 0;
        for (int i = 0; i < s.size(); i++) {
            if (i & 1) {
                if (s[i] == '1') cnt1++;
            } else {
                if (s[i] == '0') cnt1++;
            }
        }
        return min((int) s.size() - cnt1, cnt1);
    }
};