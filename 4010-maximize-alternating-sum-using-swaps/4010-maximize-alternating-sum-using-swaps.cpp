struct DSU {
    vector<int> parent, size;
    DSU(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);
        size.assign(n + 1, 1);
    }
    int find(int x) {
        return x == parent[x] ? x : (x = find(parent[x]));
    }
    void unite(int a, int b) {
        int pa = find(a);
        int pb = find(b);
        if (pa != pb) {
            if (size[pb] > size[pa]) swap(pa, pb);
            size[pa] += size[pb];
            parent[pb] = pa;
        }
    }
};
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums, vector<vector<int>>& swaps) {
        int n = nums.size();
        int m = swaps.size();
        DSU dsu(n);
        for (auto &sw : swaps)
            dsu.unite(sw[0], sw[1]);
        unordered_map<int,vector<int>> parToList;
        for (int i = 0; i < n; i++) parToList[dsu.find(i)].push_back(i);
        vector<int> v = nums;
        for (auto &[par, list] : parToList) {
            vector<int> oddIdx, evenIdx;
            for (auto idx : list) {
                if (idx & 1) oddIdx.push_back(idx);
                else evenIdx.push_back(idx);
            }
            sort(list.begin(), list.end(), [&](int i, int j) {
                return nums[i] > nums[j];
            });
            int i = 0;
            for (auto j : evenIdx) v[j] = nums[list[i++]];
            for (auto j : oddIdx) v[j] = nums[list[i++]];
        }
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            if (i & 1) ans -= v[i];
            else ans += v[i];
        }
        return ans;
    }
};