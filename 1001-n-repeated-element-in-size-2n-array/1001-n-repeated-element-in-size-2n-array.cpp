class Solution {
public:
    int repeatedNTimes(vector<int>& nums) {
        unordered_map<int,int> f;
        for (auto x : nums) if (++f[x] == 2) return x;
        return -1;
    }
};