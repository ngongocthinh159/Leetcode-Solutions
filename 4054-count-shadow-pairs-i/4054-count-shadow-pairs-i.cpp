struct query {
    int idx, val;
};
class Solution {
public:
    long long shadowPairs(vector<int>& nums) {
        int n = nums.size();
        vector<int> st;
        vector<int> R(n);
        vector<query> q;
        unordered_map<int,vector<int>> idxToQIdx;
        for (int i = n - 1; i >= 0; i--) {
            while (st.size() && (nums[st.back()] >= nums[i])) st.pop_back();
            R[i] = st.size() ? st.back() : n;
            q.push_back(query{i + 1, nums[i]});
            q.push_back(query{R[i], nums[i]});
            int idx1 = q.size() - 2;
            int idx2 = q.size() - 1;
            idxToQIdx[i + 1].push_back(idx1);
            idxToQIdx[R[i]].push_back(idx2);

            st.push_back(i);
        }
        unordered_map<int,int> f;
        int Q = q.size();
        vector<int> ans(Q);
        for (int i = n; i >= 0; i--) {
            if (i < n) f[nums[i]]++;

            for (auto qidx : idxToQIdx[i]) {
                ans[qidx] = f[q[qidx].val];
            }
        }
        int j = 0;
        long long res = 0;
        for (int i = n - 1; i >= 0; i--) {
            res += R[i] - i - 1 - (ans[j] - ans[j + 1]);
            j += 2;
        }
        return res;
    }
};