struct DSU {
    vector<int> parent;
    vector<int> size;
    vector<array<int,4>> history;
    DSU(int n, bool auto_make_set = true) {
        parent.resize(n + 1);
        size.resize(n + 1);
        if (auto_make_set) {
            for (int i = 0; i <= n; i++) parent[i] = i, size[i] = 1;
        }
    }
    void make_set(int x) {
        parent[x] = x;
        size[x] = 1;
    }
    int find(int x) {
        return x == parent[x] ? x : find(parent[x]);
    }
    bool same_set(int a, int b) {
        return find(a) == find(b);
    }
    void unite(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if (ra != rb) {
            if (size[ra] < size[rb]) swap(ra,rb), swap(a, b);
            history.push_back({ra, size[ra], rb, parent[rb]});
            size[ra] += size[rb];
            parent[rb] = ra;
        }
    }
    void rollback() {
        auto a = history.back();
        history.pop_back();
        size[a[0]] = a[1];
        parent[a[2]] = a[3];
    }
};


class Solution {
public:
    vector<bool> friendRequests(int n, vector<vector<int>>& restrictions, vector<vector<int>>& requests) {
        DSU d(n);
        vector<bool> ans(requests.size());
        for (int i = 0; i < int(requests.size()); i++) {
            int u = requests[i][0];
            int v = requests[i][1];
            d.unite(u, v);
            bool ok = true;
            for (auto &r : restrictions) {
                if (d.same_set(r[0], r[1])) {
                    ok = false;
                    d.rollback();
                    break;
                }
            }
            if (ok) {
                d.unite(u, v);
            }
            ans[i] = ok;
        }
        return ans;
    }
};