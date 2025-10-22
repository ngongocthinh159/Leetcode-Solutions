class Solution {
public:
    void normalize(vector<int> &arr) {
        auto rank = arr;
        sort(rank.begin(), rank.end());
        rank.erase(unique(rank.begin(), rank.end()), rank.end());
        for (auto &x : arr) {
            auto it = lower_bound(rank.begin(), rank.end(), x);
            x = it - rank.begin() + 1;
        }
    }
    int hash(vector<int> &arr) {
        int res = 0, base = arr.size() + 1;
        for (int i = 0; i < arr.size(); i++)
            res = base * res + arr[i];
        return res;
    }
    vector<vector<int>> splitAndMerge(vector<int> &arr, int l, int r) {
        vector<vector<int>> res;
        vector<int> v;
        for (int i = 0; i < l; i++) v.push_back(arr[i]);
        for (int i = r + 1; i < arr.size(); i++) v.push_back(arr[i]);
        for (int i = 0; i < v.size(); i++) if (i != l) {
            vector<int> cur;
            for (int j = 0; j < i; j++) cur.push_back(v[j]);
            for (int j = l; j <= r; j++) cur.push_back(arr[j]);
            for (int j = i; j < v.size(); j++) cur.push_back(v[j]);
            res.push_back(cur);
        }
        return res;
    }
    int minSplitMerge(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        if (nums1 == nums2) return 0;
        unordered_set<int> vis;
        deque<vector<int>> q;
        q.push_front(nums1);
        vis.insert(hash(nums1));
        int level = 0;
        while (q.size()) {
            for (int sz = q.size(); sz; sz--) {
                auto u = q.back();
                q.pop_back();
                if (u == nums2) return level;
                for (int len = 1; len < n; len++) {
                    for (int l = 0; l + len - 1 < n; l++) {
                        for (auto &v : splitAndMerge(u, l, l + len - 1)) {
                            int h = hash(v);
                            if (!vis.count(h)) {
                                vis.insert(h);
                                q.push_front(v);
                            }
                        }
                    }
                }
            }
            level++;
        }
        unreachable();
    }
};