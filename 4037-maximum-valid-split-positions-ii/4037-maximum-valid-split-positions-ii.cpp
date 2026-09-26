class Solution {
public:
    int gcd(int a, int b) {
        return __gcd(a, b);
    }
    int findNormal(vector<int> &nums) {
        int n = nums.size();
        if (n <= 1) return 0;
        vector<int> pref(n);
        vector<int> suf(n);
        pref[0] = nums[0];
        suf[n - 1] = nums[n - 1];
        for (int i = 1; i < n; i++) {
            pref[i] = gcd(pref[i - 1], nums[i]);
        }
        for (int i = n - 2; i >= 0; i--) {
            suf[i] = gcd(suf[i + 1], nums[i]);
        }
        int cnt = 0;
        for (int i = 0; i < n - 1; i++) {
            if (pref[i] == suf[i + 1]) cnt++;
        }
        return cnt;
    }
    int maxValidSplits(vector<int>& nums) {
        int n = nums.size();
        vector<int> pref(n);
        vector<int> suf(n);
        unordered_map<int,array<int,2>> p;
        unordered_map<int,array<int,2>> s;
        for (int i = 0; i < n; i++) {
            if (i == 0) pref[i] = nums[i];
            else {
                pref[i] = gcd(pref[i - 1], nums[i]);
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            if (i == n - 1) suf[i] = nums[i];
            else {
                suf[i] = gcd(suf[i + 1], nums[i]);
            }
        }
        for (int i = 0; i < n; ) {
            int start = i, end = i;
            while (i + 1 < n && pref[i] == pref[i + 1]) i++, end = i;
            p[pref[start]] = {start, end};
            i++;
        }
        for (int i = 0; i < n; ) {
            int start = i, end = i;
            while (i + 1 < n && suf[i] == suf[i + 1]) i++, end = i;
            s[suf[start]] = {start, end};
            i++;
        }

        vector<array<int,3>> v;
        auto add = [&](vector<array<int,3>> &v, int x, int idx, int mode) {
            for (auto &a : v) a[0] = gcd(a[0], x);
            v.push_back({x, idx, idx});
            vector<array<int,3>> tmp;
            if (mode == 1) {
                for (int i = int(v.size()) - 1; i >= 0; ) {
                    int end = i, start = i;
                    while (i - 1 >= 0 && v[i][0] == v[i - 1][0]) i--, start = i;
                    tmp.push_back({v[start][0], v[start][1], v[end][2]});
                    i--;
                }
            } else {
                for (int i = int(v.size()) - 1; i >= 0; ) {
                    int end = i, start = i;
                    while (i - 1 >= 0 && v[i][0] == v[i - 1][0]) i--, start = i;
                    tmp.push_back({v[end][0], v[end][1], v[start][2]});
                    i--;
                }
            }
            reverse(tmp.begin(), tmp.end());
            swap(v, tmp);
        };
        auto find = [](int l1, int r1, int l2, int r2) -> int {
            if (l1 > r2 || l2 > r1) return 0;
            return min(r1,r2) - max(l1,l2) + 1;
        };
        vector<int> ans(n);
        for (int j = 1; j < n - 1; j++) {
            int cnt = 0;
            if (pref[j - 1] == suf[j + 1]) cnt++;

            if (j - 1 > 0) {
                add(v, nums[j - 1], j - 1, 1);
                for (auto &a : v) {
                    int tar = gcd(a[0], suf[j + 1]);
                    int S = a[1] - 1;
                    int R = a[2] - 1;
                    if (p.count(tar))
                        cnt += find(S, R, p[tar][0], p[tar][1]);
                }
            }

            ans[j] = cnt;
        }
        v.clear();
        for (int j = n - 2; j >= 1; j--) {
            int cnt = 0;

            if (j + 1 < n - 1) {
                add(v, nums[j + 1], j + 1, 2);
                for (auto &a : v) {
                    int tar = gcd(a[0], pref[j - 1]);
                    int S = a[1] + 1;
                    int R = a[2] + 1;
                    if (s.count(tar))
                        cnt += find(S, R, s[tar][0], s[tar][1]);
                }
            }

            ans[j] += cnt;
        }
        int all = findNormal(nums);
        vector<int> tmp;
        for (int i = 1; i < n; i++) tmp.push_back(nums[i]);
        ans[0] = findNormal(tmp);
        nums.pop_back();
        ans[n - 1] = findNormal(nums);
        int res = 0;
        for (int i = 0; i < n; i++) res = max(res, ans[i]);
        res = max(res, all);
        return res;
    }
};