class Solution {
public:
    vector<string> largestString(vector<int>& nums) {
        int n = nums.size();
        vector<string> res;
        int z = (1 << 25);
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            string s = "";
            while (x >= z) {
                s += 'z';
                x -= z;
            }
            for (int bit = 25; bit >= 0; bit--) if ((x >> bit) & 1) s += bit + 'a';
            res.push_back(s);
        }
        return res;
    }
};