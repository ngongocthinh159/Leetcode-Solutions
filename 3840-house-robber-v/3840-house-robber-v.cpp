class Solution {
public:
    long long rob(vector<int>& nums, vector<int>& colors) {
        int n = nums.size();
        long long a = 0, b = 0, na, nb, LINF = 1e18 + 5;
        int pc = -1;
        for (int i = 0; i < n; i++) {
            if (colors[i] != pc) {
                na = max(a, b);
                nb = nums[i] + max(a, b);
            } else {
                na = max(a, b);
                nb = nums[i] + a;
            }
            a = na;
            b = nb;
            pc = colors[i];
        }
        return max(a, b);
    }
};