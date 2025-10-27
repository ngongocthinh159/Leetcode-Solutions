class Solution {
public:
    int numberOfBeams(vector<string>& bank) {
        int n = bank.size();
        int m = bank[0].size();
        int last = 0, ans = 0;
        for (int i = 0; i < n; i++) {
            int cnt = 0;
            for (int j = 0; j < m; j++) if (bank[i][j] == '1') cnt++;
            if (cnt != 0) {
                if (last != 0)
                    ans += cnt * last;
                last = cnt;
            }
        }
        return ans;
    }
};