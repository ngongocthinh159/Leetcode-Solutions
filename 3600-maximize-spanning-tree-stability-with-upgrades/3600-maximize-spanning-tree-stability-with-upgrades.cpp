struct dsu {
    vector<int> parent;
    vector<int> size;
    dsu(int n) {
        size.assign(n, 1);
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }
    void unite(int a, int b) {
        int pa = find(a);
        int pb = find(b);
        if (pa != pb) {
            if (size[pb] > size[pa]) swap(pa, pb);
            size[pa] += size[pb];
            parent[pb] = pa;
        }
    }
    bool same(int a, int b) {
        return find(a) == find(b);
    }
};
class Solution {
public:
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        dsu d(n);
        vector<vector<int>> v;
        int ans = 1e9 + 5;
        for (auto &e : edges) {
            if (e[3] == 1) {
                if (d.same(e[0], e[1])) return -1;
                d.unite(e[0], e[1]);
                ans = min(ans, e[2]);
            } else v.push_back(e);
        }
        sort(v.begin(), v.end(), [](auto &v1, auto &v2) {
            return v1[2] > v2[2];
        });
        vector<int> tmp;
        for (auto &e : v) {
            if (!d.same(e[0], e[1])) {
                d.unite(e[0], e[1]);
                tmp.push_back(e[2]);
            }
        }
        for (int i = 1; i < n; i++) if (!d.same(0, i)) return -1;
        for (int i = int(tmp.size()) - 1; i >= 0; i--) {
            if (k) {
                k--;
                ans = min(ans, tmp[i] * 2);
            } else ans = min(ans, tmp[i]);
        }
        return ans;
    }
};