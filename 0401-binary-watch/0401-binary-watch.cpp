class Solution {
public:
    vector<string> readBinaryWatch(int turnedOn) {
        vector<string> res;
        int fmask = (1 << 10) - 1;
        for (int mask = 0; mask <= fmask; mask++) {
            if (__builtin_popcount(mask) == turnedOn) {
                int h = mask >> 6;
                int m = mask & ((1 << 6) - 1);
                if (h <= 11 && m <= 59) {
                    string hs = to_string(h);
                    string ms = to_string(m);
                    if (ms.size() != 2) ms = "0" + ms;
                    res.push_back(hs + ":" + ms);
                }
            }
        }
        return res;
    }
};