class Solution {
public:
    int minDeletionSize(vector<string>& strs) {

        int n = strs.size();
        int m = strs[0].size();
        vector<pair<int,int>> v;
        for (int i = 1; i < n; i++) v.push_back({i - 1, i});
        int ans = 0;
        for (int i = 0; i < m; i++) {
            bool canKeep = true;
            vector<pair<int,int>> equal;
            for (auto &[i1, i2] : v) {
                if (strs[i1][i] > strs[i2][i]) {
                    canKeep = false;
                    break;
                } else if (strs[i1][i] == strs[i2][i])
                    equal.push_back({i1, i2});
            }
            if (canKeep) {
                swap(v, equal);
            } else
                ans++;
        }
        return ans;
    }
};