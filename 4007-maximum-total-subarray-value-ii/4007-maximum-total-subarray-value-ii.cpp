#define LOG 18
#define N 100005
int rmq[LOG + 1][N];
class Solution {
public:
    int query(int l, int r) {
        int msb = 32 - __builtin_clz(r - l + 1) - 1;
        return max(rmq[msb][l], rmq[msb][r - (1 << msb) + 1]);
    }
    long long maxTotalValue(vector<int>& nums, int k) {
        int n = nums.size();

        for (int i = 0; i < n; i++) rmq[0][i] = nums[i];
        for (int j = 1; j <= LOG; j++)
            for (int i = 0; i + (1 << j) - 1 < n; i++)
                rmq[j][i] = max(rmq[j - 1][i], rmq[j - 1][i + (1 << (j - 1))]);

        vector<int> L(n), R(n);
        vector<int> st;
        for (int i = 0; i < n; i++) {
            while (st.size() && nums[st.back()] >= nums[i]) st.pop_back();
            if (st.size())
                L[i] = st.back();
            else
                L[i] = -1;
            st.push_back(i);
        }
        st.clear();
        auto cmp = [&](auto &v1, auto &v2) {
            return query(v1[1], v1[2]) - nums[v1[0]] < query(v2[1], v2[2]) - nums[v2[0]];  
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> q(cmp);
        set<pair<int,int>> S;
        for (int i = n - 1; i >= 0; i--) {
            while (st.size() && nums[st.back()] > nums[i]) st.pop_back();
            if (st.size())
                R[i] = st.back();
            else
                R[i] = n;
            st.push_back(i);
            q.push({i, L[i] + 1, R[i] - 1});
            S.insert({L[i] + 1, R[i] - 1});
        }
        long long ans = 0;
        while (k--) {
            auto v = q.top(); q.pop();
            int idx = v[0];
            int l = v[1];
            int r = v[2];
            ans += query(l, r) - nums[idx];
            // cout << l << ' ' << r << ' ' << query(l, r) - nums[idx] << ' ' << idx << '\n';
            if (l + 1 <= idx && l + 1 <= r && !S.count({l + 1, r})) q.push({idx, l + 1, r}), S.insert({l + 1, r});
            if (r - 1 >= idx && l <= r - 1 && !S.count({l, r - 1})) q.push({idx, l, r - 1}), S.insert({l, r - 1});
        }
        return ans;
    }
};