struct segtree {
    vector<int> nodes;
    int n;
    segtree(int _n) {
        n = _n;
        nodes.resize(4*n);
    }
    void update(int idx, int s, int e, int pos, int val) {
        if (s == e) {
            nodes[idx] += val;
            return;
        }
        int m = (s + e)/2;
        if (pos <= m)
            update(2*idx, s, m, pos, val);
        else
            update(2*idx + 1, m + 1, e, pos, val);
        nodes[idx] = max(nodes[2*idx], nodes[2*idx + 1]);
    }
    int query(int idx, int s, int e, int l, int r) {
        if (s > r || l > e || s > e || l > r) return 0;
        if (l <= s && e <= r) return nodes[idx];
        int m = (s + e)/2;
        return max(query(2*idx, s, m, l, r), 
            query(2*idx + 1, m + 1, e, l, r));
    }
};
class Solution {
public:
    int maxJumps(vector<int>& arr, int d) {
        int n = arr.size();
        vector<int> dp(n), order(n), L(n), R(n);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int i, int j) {
            return arr[i] < arr[j];
        });
        vector<int> st;
        for (int i = 0; i < n; i++) {
            while (st.size() && arr[st.back()] < arr[i]) st.pop_back();
            if (st.size()) L[i] = st.back();
            else L[i] = -1;
            st.push_back(i);
        }
        st.clear();
        for (int i = n - 1; i >= 0; i--) {
            while (st.size() && arr[st.back()] < arr[i]) st.pop_back();
            if (st.size()) R[i] = st.back();
            else R[i] = n;
            st.push_back(i);
        }
        segtree tree(n);
        int ans = 0;
        for (int k = 0; k < n; k++) {
            int i = order[k];
            dp[i] = 1;
            dp[i] = max(dp[i], 1 + tree.query(1, 0, n - 1, i + 1, min(R[i] - 1, i + d)));
            dp[i] = max(dp[i], 1 + tree.query(1, 0, n - 1, max(L[i] + 1, i - d), i - 1));
            tree.update(1, 0, n - 1, i, dp[i]);
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};