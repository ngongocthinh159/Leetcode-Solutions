class Solution {
public:
    string makeLargestSpecial(string s) {
        int n = s.size();
        auto find = [&](int i, string &t) {
            int open = -1, j;
            while (i < n && open != 0) {
                j = i;
                if (open == -1) open = 0;
                if (t[i] == '1') open++;
                else open--;
                if (open < 0) return -1;
                i++;
            }
            if (open == 0) return j;
            return -1;
        };
        auto swap_str = [](int l, int m, int r, string &s) {
            // shift left
            reverse(s.begin() + l, s.begin() + m + 1);
            reverse(s.begin() + m + 1, s.begin() + r + 1);
            reverse(s.begin() + l, s.begin() + r + 1);
        };
        while (1) {
            bool found = false;

            for (int i = 0; i < n - 1; i ++) {
                int j = find(i, s);
                // cout << i << ' ' << j << '\n';
                if (j == -1 || j == n - 1) continue;
                int k = find(j + 1, s);
                // cout << i << ' ' << j << ' ' << k << '\n';
                if (k != -1) {
                    if (s.substr(i, j - i + 1) < s.substr(j + 1, k - (j + 1) + 1)) {
                        swap_str(i, j, k, s);
                        // cout << s << '\n';
                        found = true;
                    }
                }
                if (found) break;
            }

            if (!found) break;
        }
        return s;
    }
};