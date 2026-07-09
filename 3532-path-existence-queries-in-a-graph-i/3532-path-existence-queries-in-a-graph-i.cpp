class Solution {
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<int> id(n);
        int cid = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (i != n - 1 && nums[i + 1] - nums[i] > maxDiff) cid++;
            id[i] = cid;
        }
        int m = queries.size();
        vector<bool> ans(m); 
        for (int i = 0; i < m; i++) {
            ans[i] = id[queries[i][0]] == id[queries[i][1]];
        }
        return ans;
    }
};