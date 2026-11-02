class Solution {
public:
    int solve(vector<int> &h) {
        int n = h.size();
        vector<int> st;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int l = -1, r = st.size();
            while (r - l > 1) {
                int m = l + (r - l)/2;
                if (h[st[m]] >= h[i]) 
                    r = m;
                else 
                    l = m;
            }
            
            if (r != st.size()) {
                int idx = st[r];
                ans = max(ans, (i - idx) * h[i]);
            }
            if (st.empty() || h[st.back()] <= h[i]) st.push_back(i);
        }
        return ans;
    }
    int maxArea(vector<int>& height) {
        int ans = solve(height);
        reverse(height.begin(), height.end());
        ans = max(ans, solve(height) );
        return ans;
    }
};