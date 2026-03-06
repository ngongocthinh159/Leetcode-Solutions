class Solution {
public:
    const int BIT = 17;
    int minimumOR(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        auto row = grid;
        int res = 0;
        for (int bit = BIT - 1; bit >= 0; bit--) {
            bool ok = true;
            for (int i = 0; i < n; i++) {
                bool found = false;
                for (auto x : row[i]) if (!((x >> bit) & 1)) {
                    found = true;
                    break;
                }
                if (!found) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                for (int i = 0; i< n; i++) {
                    vector<int> nr;
                    for (auto x : row[i]) if (!((x >> bit) & 1)) nr.push_back(x);
                    row[i] = nr;
                }
            } else {
                res |= (1 << bit);
            }
        }
        return res;
    }
};