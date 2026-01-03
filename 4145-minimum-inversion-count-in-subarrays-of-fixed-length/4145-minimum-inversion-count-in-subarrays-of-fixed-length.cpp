struct FenwickTree {
    vector<int> bit;  // binary indexed tree
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(vector<int> const &a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};
class Solution {
public:
    long long minInversionCount(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> norm = nums;
        sort(norm.begin(), norm.end());
        norm.erase(unique(norm.begin(), norm.end()), norm.end());
        int sz = norm.size();
        FenwickTree tree(sz);
        unordered_map<int,int> numToIdx;
        for (int i = 0; i < n; i++) {
            auto idx = lower_bound(norm.begin(), norm.end(), nums[i]) - norm.begin();
            numToIdx[nums[i]] = idx;
        }
        long long ans = LLONG_MAX;
        long long inversions = 0;
        for (int r = 0; r < n; r++) {
            int x = numToIdx[nums[r]];

            if (r - k >= 0) {
                int y = numToIdx[nums[r - k]];
                if (y - 1 >= 0) inversions -= tree.sum(0, y - 1);
                tree.add(y, -1);
            }

            if (x + 1 < sz) inversions += tree.sum(x + 1, sz - 1);
            tree.add(x, 1);
            
            if (r >= k - 1) ans = min(ans, inversions);
        }
        return ans;
    }
};