class Solution {
public:
    int reverseBits(int n) {
        for (int i = 0, j = 31; i < j; i++, j--) {
            int x = (n >> i) & 1;
            int y = (n >> j) & 1;
            if (y^x) n ^= (1 << j), n ^= (1 << i);
        }
        return n;
    }
};