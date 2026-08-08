class Solution {
public:
    string smallestNumber(string num, long long t) {
        int n = num.size();
        // 2 -> x: a2 + 2 * a4 + 3 * a8 + a6 = x
        // 3 -> y: a3 + 2 * a9 + a6 = y - a6
        // 5 -> z: a5 = z
        // 7 -> t: a7 = t
        int leftMostZeroIdx = -1;
        for (int i = n - 1; i >= 0; i--) if (num[i] == '0') leftMostZeroIdx = i;
        vector<int> p = {2, 3, 5, 7};
        map<int,int> f;
        long long T = t;
        for (auto x : p) {
            int cnt = 0;
            while (T % x == 0) T /= x, cnt++;
            f[x] = cnt;
        }
        if (T != 1) return "-1";

        vector<long long> remain(n + 1);
        remain[0] = t;
        for (int i = 1; i <= n; i++) remain[i] = remain[i - 1] / gcd(remain[i - 1], 1ll * (num[i - 1] - '0'));
        if (remain[n] == 1 && leftMostZeroIdx == -1) {
            return num;
        }

        int start = leftMostZeroIdx == -1 ? n - 1 : leftMostZeroIdx;
        for (int i = start; i >= 0; i--) {
            for (int j = num[i] - '0' + 1; j < 10; j++) {
                long long tNow = remain[i] / gcd(remain[i], 1ll * j);

                if (tNow == 1) {
                    string t = "";
                    for (int p = 0; p < i; p++) t += num[p];
                    t += j + '0';
                    while (t.size() < n) t += '1';
                    return t;
                }

                string t = "";
                for (int ii = n - 1; ii > i; ii--) {
                    for (int jj = 9; jj >= 1; jj--) if (tNow % jj == 0) {
                        tNow /= jj;
                        t += jj + '0';
                        if (tNow == 1) {
                            for (int p = ii - 1; p > i; p--) t += '1';
                            t += j + '0';
                            for (int p = i - 1; p >= 0; p--) t += num[p];
                            reverse(t.begin(), t.end());
                            return t;
                        }
                        break;
                    }
                }
            }
        }
        string res = "";
        for (int i = 9; i >= 2; i--) {
            while (t % i == 0) res += i + '0', t /= i;
        }
        while (res.size() <= n) res += '1';
        sort(res.begin(), res.end());
        return res;
    }
};