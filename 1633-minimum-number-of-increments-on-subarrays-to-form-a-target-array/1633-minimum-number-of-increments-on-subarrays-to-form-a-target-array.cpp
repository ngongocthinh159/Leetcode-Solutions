class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        int n = target.size(), ans = 0;
        vector<int> st;
        vector<int> L(n), R(n);
        for (int i = 0; i < n; i++) {
            while (st.size() && target[st.back()] > target[i]) st.pop_back();
            if (st.size())
                L[i] = target[st.back()];
            else
                L[i] = 0;
            st.push_back(i);
        }
        st.clear();
        for (int i = n - 1; i >= 0; i--) {
            while (st.size() && target[st.back()] >= target[i]) st.pop_back();
            if (st.size())
                R[i] = target[st.back()];
            else
                R[i] = 0;
            st.push_back(i);
            ans += target[i] - max(L[i], R[i]);
        }
        return ans;
    }
};