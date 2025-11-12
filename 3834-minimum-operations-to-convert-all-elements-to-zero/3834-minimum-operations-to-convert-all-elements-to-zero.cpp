class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        vector<int> st, L(n);
        for (int i = 0; i < n; i++) {
            while (st.size() && nums[st.back()] > nums[i]) st.pop_back();
            if (st.size())
                L[i] = st.back();
            else
                L[i] = -1;
            if (nums[i])
                if (!st.size() || nums[st.back()] != nums[i]) ans++;
            st.push_back(i);
        }
        return ans;
    }
};