#define ll long long
#define data __data
struct data {
    int mn, mx;
};
struct segtree {
    vector<data> nodes;
    vector<int> lazy;
    segtree(int _n) {
        nodes.resize(4*_n);
        lazy.resize(4*_n);
    }
    data merge(data &l, data &r) {
        data res;
        res.mn = min(l.mn, r.mn);
        res.mx = max(l.mx, r.mx);
        return res;
    }
    void apply(int idx, int s, int e, int delta) {
        nodes[idx].mn += delta;
        nodes[idx].mx += delta;
        lazy[idx] += delta;
    }
    void push_down(int idx, int s, int e) {
        if (lazy[idx]) {
            int m = (s + e)/2;
            apply(2*idx, s, m, lazy[idx]);
            apply(2*idx + 1, m + 1, e, lazy[idx]);
            lazy[idx] = 0;
        }
    }
    void update(int idx, int s, int e, int l, int r, int delta) {
        if (s > r || l > e || s > e || l > r) return;
        if (l <= s && e <= r) {
            apply(idx, s, e, delta);
            return;
        }
        push_down(idx, s, e);
        int m = (s + e)/2;
        update(2*idx, s, m, l, r, delta);
        update(2*idx + 1, m + 1, e, l, r, delta);
        nodes[idx] = merge(nodes[2*idx], nodes[2*idx + 1]);
    }
    data query() {
        return nodes[1];
    }
};
struct rec {
    int top, left, bot, right;
};
class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rs) {
        int n = rs.size();
        vector<rec> v(n);
        vector<int> y;
        for (int i = 0; i < n; i++) {
            v[i] = rec{rs[i][3], rs[i][0], rs[i][1], rs[i][2]};
            y.push_back(v[i].top - 1);
            y.push_back(v[i].bot);
        }
        sort(y.begin(), y.end());
        y.erase(unique(y.begin(), y.end()), y.end());
        unordered_map<int,int> toIdx;
        for (int i = 0; i < int(y.size()); i++) toIdx[y[i]] = i;
        vector<array<int,4>> es;
        for (int i = 0; i < n; i++) {
            es.push_back(array<int,4>{v[i].left, 1, toIdx[v[i].bot], toIdx[v[i].top - 1]});
            es.push_back(array<int,4>{v[i].right, -1, toIdx[v[i].bot], toIdx[v[i].top - 1]});
        }
        int sz = y.size();
        segtree tree(sz);
        sort(es.begin(), es.end());
        for (int i = 0; i < int(es.size()); ) {
            int x = es[i][0];
            while (i < int(es.size()) && x == es[i][0]) {
                tree.update(1, 0, sz - 1, es[i][2], es[i][3], es[i][1]);
                i++;
            }
            if (i < int(es.size())) {
                if (tree.query().mn != 1 || tree.query().mx != 1) return false;
            }
        }
        return true;
    }
};