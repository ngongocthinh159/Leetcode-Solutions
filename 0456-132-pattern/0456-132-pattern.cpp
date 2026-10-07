class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        int n = nums.size();
        int mx = INT_MIN;
        vector<int> st;
        for (int i = n - 1; i >= 0; i--) {
            if (mx > nums[i]) return true;

            while (st.size() && nums[st.back()] < nums[i]) {
                mx = max(mx, nums[st.back()]);
                st.pop_back();
            }
            st.push_back(i);
        }
        return false;
    }
};