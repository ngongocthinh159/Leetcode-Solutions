class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        int n = nums.size(), m = queries.size();
        unordered_map<int,vector<int>> idxToQIdx;
        for (int i = 0 ;i < m; i++) idxToQIdx[queries[i]].push_back(i);
        vector<int> v = nums;
        v.insert(v.end(), nums.begin(), nums.end());
        unordered_map<int,int> last;
        vector<int> ans(m, INT_MAX);
        for (int i = 0; i < 2*n; i++) {
            for (auto qidx : idxToQIdx[i%n]) {
                if (last.count(v[i]))
                    ans[qidx] = min(ans[qidx], i - last[v[i]]);
            }
            last[v[i]] = i;
        }
        last.clear();
        for (int i = 2*n - 1; i >= 0; i--) {
            for (auto qidx : idxToQIdx[i%n]) {
                if (last.count(v[i]))
                    ans[qidx] = min(ans[qidx], last[v[i]] - i);
            }
            last[v[i]] = i;
        }
        for (int i = 0; i < m; i++) if (ans[i] == n) ans[i] = -1;
        return ans;
    }
};