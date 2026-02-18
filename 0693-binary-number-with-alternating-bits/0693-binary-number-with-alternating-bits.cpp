class Solution {
public:
    bool hasAlternatingBits(int n) {
        int mxb = __lg(n);
        for (int bit = 1; bit <= mxb; bit++) if (((n >> bit) & 1) == ((n >> (bit - 1)) & 1))
            return false;
        return true;
    }
};