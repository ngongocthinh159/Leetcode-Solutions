class Solution {
public:
    long long minInitialStrength(vector<int>& monsters, vector<vector<int>>& boosts) {
        long long sum = 0;
        for (auto x : monsters) sum += x;
        int n = monsters.size();
        int m = boosts.size();
        vector<long long> b(n + 1);
        for (auto &c : boosts) {
            b[c[0]] += c[2];
            b[c[1] + 1] -= c[2];
        }
        for (int i = 1; i <= n; i++) b[i] += b[i - 1];

        long long l = -1, r = sum + 1;
        while (r - l > 1) {
            long long m = l + (r - l)/2;
            bool ok = true;

            long long cur = m;
            for (int i = 0; i < n; i++) {
                if (cur + b[i] < monsters[i]) {
                    ok = false;
                    break;
                }
                cur -= monsters[i];
                cur = max(cur, 0ll);
            }

            if (ok)
                r = m;
            else
                l = m;
        }
        return r;
    }
};