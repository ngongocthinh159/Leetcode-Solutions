class Solution {
public:
    long long shadowPairs(vector<int>& nums) {
        int n = nums.size();
        vector<pair<int,int>> st;
        int cnt = 0;
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            while (st.size() && (nums[st.back().first] > nums[i])) {
                cnt -= st.back().second;
                st.pop_back();
            }

            if (st.empty()) {
                st.push_back({i, 1});
                cnt++;
            }
            else {
                if (nums[st.back().first] == nums[i]) st.back().second++;
                else st.push_back({i, 1});
                cnt++;
            }
            ans += cnt - st.back().second;
        }
        return ans;
    }
};