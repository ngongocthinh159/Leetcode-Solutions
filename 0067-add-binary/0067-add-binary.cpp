class Solution {
public:
    string addBinary(string a, string b) {
        int carry = 0;
        string res = "";
        int i = 0;
        for (; i < min(a.size(), b.size()); i++) {
            int x = a[a.size() - 1 + 0 - i] - '0'; 
            int y = b[b.size() - 1 + 0 - i] - '0';
            int cur = (x + y + carry) % 2;
            carry = (x + y + carry) / 2;
            res += cur ? '1' : '0';
        }
        while (i < a.size()) {
            int x = a[a.size() - 1 + 0 - i] - '0';
            int cur = (x + carry) % 2;
            carry = (x + carry) / 2;
            res += cur ? '1' : '0';
            i++;
        }
        while (i < b.size()) {
            int x = b[b.size() - 1 + 0 - i] - '0';
            int cur = (x + carry) % 2;
            carry = (x + carry) / 2;
            res += cur ? '1' : '0';
            i++;
        }
        if (carry) res.push_back('1');
        reverse(res.begin(), res.end());
        return res;
    }
};