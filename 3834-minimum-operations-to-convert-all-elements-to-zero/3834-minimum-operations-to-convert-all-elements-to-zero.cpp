class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        vector<int> st, L(n);
        unordered_map<int,int> f;
        for (int i = 0; i < n; i++) {
            while (st.size() && nums[st.back()] >= nums[i]) st.pop_back();
            if (st.size())
                L[i] = st.back();
            else
                L[i] = -1;
            st.push_back(i);
            if (!nums[i]) continue;

            if (!f.count(nums[i]) || (f[nums[i]] <= L[i])) ans++;
            f[nums[i]] = i;
        }
        return ans;
    }
};