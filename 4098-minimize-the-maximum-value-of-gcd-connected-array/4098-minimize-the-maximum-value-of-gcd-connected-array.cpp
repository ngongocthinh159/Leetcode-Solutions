class Solution {
public:
    long long find(int x) {
        for (int i = 2; i <= sqrt(x); ++i) if (x % i == 0) {
            return i;
        }
        return x;
    }
    long long minimumMaxValue(int n, int index, int value) {
        if (value == 1) return -1; 
        long long lenL = index;
        long long lenR = n - index - 1;
        if (value % 2 == 0) {
            long long L = value - 2 * lenL;
            if (L <= 1) return -1;
            long long R = value + 2 * lenR;
            return R;
        } else {
            long long spf = find(value);
            long long L = value;
            if (lenL >= 1) L += -spf - (lenL - 1) * 2;
            if (L <= 1) return -1;
            long long R = value;
            if (lenR >= 1) R += spf + (lenR - 1) * 2;
            return R;
        }
    }
};