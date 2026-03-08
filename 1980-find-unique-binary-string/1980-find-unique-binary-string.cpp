class Solution {
public:
    int toInt(string &s) {
        int n = s.size();
        int res = 0;
        for (int bit = 0; bit < n; bit++) {
            if (s[n - 1 - bit] - '0') res |= (1 << bit);
        }
        return res;
    }
    string toString(int x, int n) {
        string res = "";
        for (int i = n - 1; i >= 0; i--) {
            if ((x >> i) & 1) res += '1';
            else res += '0';
        }
        return res;
    }
    string findDifferentBinaryString(vector<string>& nums) {
        int n = nums.size();
        unordered_set<int> S;
        for (auto &s : nums) {
            S.insert(toInt(s));
        }
        for (int i = 0; i < (1 << n); i++) {
            if (!S.count(i)) {
                return toString(i, n);
            }
        }
        return "-1";
    }
};