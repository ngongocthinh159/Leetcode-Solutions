class Solution {
public:
    int countNegatives(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int l = -1, r = m; 
            while (r - l > 1) {
                int mid = l + (r - l)/2;
                if (grid[i][mid] >= 0)
                    l = mid;
                else
                    r = mid;
            }
            ans += m - l - 1;
        }
        return ans;
    }
};