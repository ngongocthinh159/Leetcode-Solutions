class Solution {
public:
    vector<int> z_function(const vector<int>& s) {
        int n = s.size();
        vector<int> z(n);

        for (int i = 1, l = 0, r = 0; i < n; ++i) {
            if (i <= r)
                z[i] = min(r - i + 1, z[i - l]);

            while (i + z[i] < n &&
                s[z[i]] == s[i + z[i]])
                ++z[i];

            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }

        return z;
    }
    int intersect(int x1, int y1, int x2, int y2) {
        if (x1 > y2 || x2 > y1 || x1 > y1 || x2 > y2) return 0;
        return min(y1,y2) - max(x1,x2) + 1;
    }
    vector<int> countSuffix(vector<int>& nums, vector<int>& target) {
        int n = nums.size(), m = target.size();
        vector<int> ans(m - n + 1);
        vector<int> s = nums;
        s.push_back(1e6);
        s.insert(s.end(), target.begin(), target.end());
        auto z = z_function(s);
        int unmatch = 0;
        unordered_map<int,int> diff;
        for (auto x : nums) diff[x]--;
        for (int i = 0; i < n; ++i) diff[target[i]]++;
        for (auto [x, cnt] : diff) if (cnt != 0) unmatch++;
        vector<int> p(m);
        p[0] = 1;
        for (int i = 1; i < m; ++i)
            p[i] = (target[i] <= target[i - 1] ? p[i - 1] : 0) + 1;
        auto add = [&](int x, int delta) {
            if (diff[x] != 0) unmatch--;
            diff[x] += delta;
            if (diff[x] != 0) unmatch++;
        };
        for (int i = n - 1; i < m; ++i) {
            if (i - n >= 0) add(target[i - n], -1);
            if (i != n - 1) add(target[i], 1);
            int l = i - n + 1;
            if (unmatch != 0) {
                ans[l] = 0;
            } else {
                int R2 = i;
                int L2 = max(l, R2 - p[i] + 1);
                int L1 = l;
                int R1 = L1 + z[n + 1 + l];
                ans[l] = intersect(L1, R1, L2, R2);
            }
        }
        return ans;
    }
};