class Solution {
public:
    long long countStableSubarrays(vector<int>& capacity) {
        long long ans = 0;
        int n = capacity.size();
        unordered_map<long long,unordered_map<long long, long long>> f;
        vector<long long> pref(n +  1);
        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + capacity[i];
            ans += f[pref[i + 1] - 3LL * capacity[i]][capacity[i]];
            if (i - 2 >= 0)
                f[pref[i - 1]][capacity[i - 1]]++;
            if (i == 1)
                f[0][capacity[0]]++;
        }
        return ans;
    }
};