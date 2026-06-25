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
        if (l > r) return 0;
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};
class Solution {
public:
    int countMajoritySubarrays(vector<int>& nums, int target) {
        // f[target_i] - f[target_j] > (i - j) / 2
        // 2 * f[i] - 2 * f[j] > (i - j)
        // 2 * f[i] - i > 2 * f[j] - j 
        // -> 2 * f[j] - j <= 2 * f[i] - i - 1
        int n = nums.size();

        vector<int> v;
        v.push_back(1);
        int f = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == target) f++;
            v.push_back(2*f - i);
            v.push_back(2*f - i - 1);
        }
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        unordered_map<int,int> toIdx;
        for (int i = 0; i < int(v.size()); i++) toIdx[v[i]] = i;
        
        int sz = v.size();
        FenwickTree tree(sz);
        tree.add(toIdx[1], 1);
        f = 0;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == target) f++;

            ans += tree.sum(0, toIdx[2*f - i - 1]);

            tree.add(toIdx[2*f - i], 1);
        }
        return ans;
    }
};