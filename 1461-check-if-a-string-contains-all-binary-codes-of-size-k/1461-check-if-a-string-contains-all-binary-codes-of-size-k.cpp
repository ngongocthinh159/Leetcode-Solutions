class Solution {
public:
    bool hasAllCodes(string s, int k) {
        int n = s.size();
        int sz = (1 << k);
        if (sz > n) return false;
        unordered_set<int> S;
        S.reserve(1 << k);
        int cur = 0;
        for (int i = 0; i < k; i++) {
            cur <<= 1;
            cur |= (s[i] - '0');
        }
        S.insert(cur);
        for (int i = k; i < n; i++) {
            cur &= ~(1 << (k - 1));
            cur <<= 1;
            cur |= (s[i] - '0');
            S.insert(cur);
        }
        if (S.size() != (1 << k)) return false;
        return true;
    }
};