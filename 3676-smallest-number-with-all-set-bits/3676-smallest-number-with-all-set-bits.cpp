class Solution {
public:
    int smallestNumber(int n) {
        int msb = 32 - __builtin_clz(n) - 1;
        return (1 << (msb + 1)) - 1;
    }
};