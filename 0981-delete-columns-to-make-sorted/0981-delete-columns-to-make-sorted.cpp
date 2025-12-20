class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int n = strs.size(), m = strs[0].size();
        int ans = 0;
        for (int j = 0; j < m; j++) {
            char prev = 0;
            for (int i = 0; i < n; i++) {
                if (strs[i][j] < prev)  {
                    ans++;
                    break;
                }
                prev = strs[i][j];
            }
        }
        return ans;
    }
};