#define N 11
vector<string> res[N];
auto init = []{
    int fmask = (1 << 10) - 1;
    for (int mask = 0; mask <= fmask; mask++) {
        int turnedOn = __builtin_popcount(mask);
        if (turnedOn < N) {
            int h = mask >> 6;
            int m = mask & ((1 << 6) - 1);
            if (h <= 11 && m <= 59) {
                string hs = to_string(h);
                string ms = to_string(m);
                if (ms.size() != 2) ms = "0" + ms;
                res[turnedOn].push_back(hs + ":" + ms);
            }
        }
    }
    return 0;
}();
class Solution {
public:
    vector<string> readBinaryWatch(int turnedOn) {
        return res[turnedOn];
    }
};