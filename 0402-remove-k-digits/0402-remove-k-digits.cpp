class Solution {
public:
    string removeKdigits(string num, int k) {
        int n = num.size();
        if (n == k) return "0";
        string res = "";
        for (int i = 0; i < n; i++) {
            while (res.size() && res.back() > num[i] && k) {
                res.pop_back();
                k--;
            }
            res += num[i];
        }
        bool ok = false;
        string s = "";
        for (int i = 0; i < res.size(); i++) {
            if (res[i] == '0' && !ok) {
                continue;
            } else {
                ok = true;
            }
            ok = true;
            s += res[i];
        }
        while (s.size() && k) {
            s.pop_back();
            k--;
        }
        return s == "" ? "0" : s;
    }
};