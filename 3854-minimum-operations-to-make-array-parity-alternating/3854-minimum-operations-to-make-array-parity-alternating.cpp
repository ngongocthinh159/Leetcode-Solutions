class Solution {
public:
    bool ok(int x, int parity) {
        if (x < 0) x *= -1;
        if (parity == 0) return x % 2 == 0;
        else return x % 2 != 0;
    }
    vector<int> solve(vector<int> &a, int parity) {
        int n = a.size();
        int mx = INT_MIN, mn = INT_MAX;
        int c = parity, cnt = 0;
        for (int i = 0; i < n; i++) {
            if (!ok(a[i], c))
                cnt++;
            mx = max(mx, a[i]);
            mn = min(mn, a[i]);
            c ^= 1;
        }
        int best = INT_MAX;
        {
            int cmx = INT_MIN, cmn = INT_MAX;
            c = parity;
            for (int i = 0; i < n; i++) {
                int x = a[i];
                if (!ok(a[i], c)) {
                    if (x - 1 >= mn) x--;
                    else x ++;
                }
                cmx = max(cmx, x);
                cmn = min(cmn, x);
                c ^= 1;
            }
            best = min(best, cmx - cmn);
        }
        {
            int cmx = INT_MIN, cmn = INT_MAX;
            c = parity;
            for (int i = 0; i < n; i++) {
                int x = a[i];
                if (!ok(a[i], c)) {
                    if (x + 1 <= mx) x++;
                    else x--;
                }
                cmx = max(cmx, x);
                cmn = min(cmn, x);
                c ^= 1;
            }
            best = min(best, cmx - cmn);
        }
        {
            int cmx = INT_MIN, cmn = INT_MAX;
            c = parity;
            for (int i = 0; i < n; i++) {
                int x = a[i];
                if (!ok(a[i], c)) {
                    if (x == mn) x++;
                    else if (x == mx) x--;
                    else x--;
                }
                cmx = max(cmx, x);
                cmn = min(cmn, x);
                c ^= 1;
            }
            best = min(best, cmx - cmn);
        }
        return {cnt, best};
    }
    vector<int> makeParityAlternating(vector<int>& nums) {
        int n = nums.size();
        return min(solve(nums, 0), solve(nums, 1));
    }
};