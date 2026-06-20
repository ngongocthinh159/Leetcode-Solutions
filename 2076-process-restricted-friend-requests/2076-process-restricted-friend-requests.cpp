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
        return x == parent[x] ? x : parent[x] = find(parent[x]);
    }
    bool same_set(int a, int b) {
        return find(a) == find(b);
    }
    void unite(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if (ra != rb) {
            if (size[ra] < size[rb]) swap(ra,rb), swap(a, b);
            size[ra] += size[rb];
            parent[rb] = ra;
        }
    }
};


class Solution {
public:
    vector<bool> friendRequests(int n, vector<vector<int>>& restrictions, vector<vector<int>>& requests) {
        DSU d(n);
        vector<bool> ans(requests.size());
        for (int i = 0; i < int(requests.size()); i++) {
            int pu = d.find(requests[i][0]);
            int pv = d.find(requests[i][1]);
            bool ok = true;
            for (auto &r : restrictions) {
                int px = d.find(r[0]);
                int py = d.find(r[1]);
                if (make_pair(px,py) == make_pair(pu,pv) || make_pair(px,py) == make_pair(pv,pu)) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                d.unite(requests[i][0], requests[i][1]);
            }
            ans[i] = ok;
        }
        return ans;
    }
};