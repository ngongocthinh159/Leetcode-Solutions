class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        sort(potions.begin(), potions.end());
        int n = spells.size();
        int m = potions.size();
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            int l = -1, r = m;
            while (r - l > 1) {
                int mid = l + (r - l)/2;
                if (1LL * spells[i] * potions[mid] >= success)
                    r = mid;
                else
                    l = mid;
            }
            ans[i] = m - r;
        }
        return ans;
    }
};