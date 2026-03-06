class Solution {
public:
    bool checkOnesSegment(string s) {
        int n = s.size();
        int cnt = 0;
        int prev = 0;
        for (int i= 0; i <n; i++) {
            if (s[i] - '0' == 1 && prev == 0) {
                cnt++;
            }
            prev = s[i] - '0';
        }
        return cnt <= 1;
    }
};