class Solution {
public:
    int findKthNumber(int n, int k) {
        vector<int> d;
        int b[20]{};
        int len = 0, x = n;
        while (x) {
            b[len++] = x%10;
            x /= 10;
        }
        reverse(b, b + len);
        int _10pow[len];
        _10pow[0] = 1;
        for (int i = 1; i < len; i++) _10pow[i] = _10pow[i - 1] * 10;
        auto getCnt = [&](vector<int> &d) -> int {
            int comp = 0;
            for (int j = 0; j < int(d.size()); j++) {
                if (b[j] != d[j]) {
                    if (b[j] > d[j]) comp = 1;
                    else comp = -1;
                    break;
                }
            }
            int res = 0;
            if (comp == 0) {
                for (int j = 0; j <= (len - int(d.size()) - 1); j++) res += _10pow[j];
                int tmp = 0;
                for (int j = int(d.size()); j < len; j++) tmp = tmp * 10 + b[j];
                tmp++;
                res += tmp;
            } else if (comp == 1) {
                for (int j = 0; j <= (len - int(d.size())); j++) res += _10pow[j];
            } else {
                for (int j = 0; j <= (len - int(d.size()) - 1); j++) res += _10pow[j];
            }
            return res;
        };
        while (k) {
            for (int i = d.empty() ? 1 : 0; i <= 9; i++) {
                d.push_back(i);

                int cnt = getCnt(d);

                // cout << "cnt prefix: ";
                // for (auto x : d) cout << x << ' ';
                // cout << '\n';
                // cout << cnt <<'\n';
                // cout << '\n';

                if (cnt < k) {
                    k -= cnt;
                    d.pop_back();
                } else
                    break;
            } 

            k--;
        }

        // vector<string> v;
        // for (int i = 1; i <= n; i++) v.push_back(to_string(i));
        // sort(v.begin(), v.end());
        // for (auto &s : v) cout << s << '\n';

        int res = 0;
        for (auto x : d) res = res * 10 + x;
        return res;
    }
};