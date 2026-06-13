#define N 100005
int spf[N];
auto init = []{
    for (int i = 0; i < N; i++) spf[i] = i;
    for (int i = 2; i * i < N; i++) if (spf[i] == i)
        for (int j = i * i; j < N; j += i) spf[j] = min(spf[j], i);
    return 0;
}();
class Solution {
public:
    vector<int> factorize(int x) {
        vector<int> res;
        while (x != 1) {
            int fact = spf[x];
            while (x % fact == 0) x /= fact;
            res.push_back(fact);
        }
        return res;
    }
    int maxScore(vector<int>& nums, int maxVal) {
        int n = nums.size();
        int mx = max(maxVal, *max_element(nums.begin(), nums.end()));
        unordered_set<int> S;
        unordered_map<int,int>f;
        for (int i = 0; i < n; i++) {
            S.insert(nums[i]);

            auto list = factorize(nums[i]);
            int sz = list.size();
            for (int mask = 1; mask < (1 << sz); mask++) {
                int cur = 1;
                for (int j = 0; j < sz; j++) if ((mask >> j) & 1) cur *= list[j];
                f[cur]++;
            }
        }
        int ans = -1e9;
        if (S.count(1)) ans = 1;
        else ans = 0;
        for (int i = 2; i <= mx; i++) {
            if (i > maxVal && !S.count(i)) continue;

            auto list = factorize(i);
            int sz = list.size();
            int hasSamePrime = 0;
            for (int mask = 1; mask < (1 << sz); mask++) {
                int cur = 1;
                for (int j = 0; j < sz; j++) if ((mask >> j) & 1) cur *= list[j];
                if (__builtin_popcount(mask) & 1) hasSamePrime += f[cur];
                else hasSamePrime -= f[cur];
            }
            if (S.count(i)) {
                hasSamePrime--;
                ans = max(ans, i - hasSamePrime);
                // if (i == 1000) cout << hasSamePrime << '\n';
            } else {
                int cost = 1;
                if (hasSamePrime > 0) {
                    hasSamePrime--;
                }
                ans = max(ans, i - hasSamePrime - cost);
            }
        }
        return ans;
    }
};