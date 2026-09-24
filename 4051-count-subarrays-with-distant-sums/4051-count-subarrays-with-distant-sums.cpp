struct segtree {
    int n;
    vector<int> nodes;
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
        nodes[idx] = nodes[2*idx] + nodes[2*idx + 1];
    }
    int query(int idx, int s, int e, int l, int r) {
        if (s > r || l > e || s > e || l > r) return 0;
        if (l <= s && e <= r) return nodes[idx];
        int m = (s + e)/2;
        return query(2*idx, s, m, l, r) + query(2*idx + 1, m + 1, e, l, r);
    }
};

class Solution {
public:
    long long distantSubarrays(vector<int>& nums, int goal, int k) {
        int n = nums.size();
        long long sum = 0;
        vector<long long> v;
        v.push_back(0);
        for (int i = 0; i < n; i++) {
            sum += nums[i];
            v.push_back(sum);
            v.push_back(sum - goal - k);
            v.push_back(sum - goal + k);

            // sum - pref >= goal + k
            // sum - pref <= goal - k
            // pref <= sum - goal - k
            // pref >= sum - goal + k
        }
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        unordered_map<long long,int> toIdx;
        int sz = v.size();
        for (int i = 0; i < sz; i++) {
            toIdx[v[i]] = i;
        }
        segtree tree(sz);
        sum = 0;
        long long ans = 0;
        tree.update(1, 0, sz - 1, toIdx[0], 1);
        for (int i = 0; i < n; i++) {
            if (k == 0) {
                ans += i + 1;
                continue;
            }
            sum += nums[i];
            ans += tree.query(1, 0, sz - 1, 0, toIdx[sum - goal - k]);
            ans += tree.query(1, 0, sz - 1, toIdx[sum - goal + k], sz - 1);
            tree.update(1, 0, sz - 1, toIdx[sum], 1);
        }
        return ans;
    }
};