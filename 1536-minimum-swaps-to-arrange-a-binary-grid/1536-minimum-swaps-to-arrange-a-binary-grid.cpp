class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<int> cnt(n);
        for (int i = 0; i < n; i++) {
            int c = 0;
            for (int j = n - 1; j >= 0 && grid[i][j] == 0; j--) c++;
            cnt[i] = c;
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int need = n - i - 1;
            int idx = -1;
            for (int j = i; j < n; j++) {
                if (cnt[j] >= need) {
                    idx = j;
                    break;
                }
            }
            if (idx == -1) return -1;
            for (int j = idx - 1; j >= i; j--) {
                swap(grid[j], grid[j + 1]);
                swap(cnt[j], cnt[j + 1]);
            }
            ans += idx - i;
        }
        return ans;
    }
};