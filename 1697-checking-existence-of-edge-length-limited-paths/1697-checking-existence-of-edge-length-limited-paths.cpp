struct DSU {
    vector<int> parent;
    vector<int> size;
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
            if (size[ra] < size[rb]) swap(ra,rb);
            size[ra] += size[rb];
            parent[rb] = ra;
        }
    }
    int find_size(int x) {
        return size[find(x)];
    }
};
struct query {
    int u, v, limit, idx;
};
class Solution {
public:
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        int m = queries.size();
        vector<query> qs(m);
        for (int i = 0; i < m; i++) {
            qs[i].u = queries[i][0];
            qs[i].v = queries[i][1];
            qs[i].limit = queries[i][2];
            qs[i].idx = i;
        }
        sort(qs.begin(), qs.end(), [](auto &a, auto &b) {
            return a.limit < b.limit;
        });
        vector<bool> ans(m);
        DSU d(n);
        sort(edgeList.begin(), edgeList.end(), [](auto &a, auto &b) {
            return a[2] < b[2];
        });
        int totEdge = edgeList.size();
        int j = 0;
        for (int i = 0; i < m; i++) {
            int limit = qs[i].limit;
            while (j < totEdge && edgeList[j][2] < limit) {
                d.unite(edgeList[j][0], edgeList[j][1]);
                j++;
            }
            ans[qs[i].idx] = d.same_set(qs[i].u, qs[i].v);
        }
        return ans;
    }
}; 