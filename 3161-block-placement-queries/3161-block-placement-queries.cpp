#define data __data
struct data {
    int pref;
    int suf;
    int mx;
};
struct Ret {
    data val;
    int L;
    int R;
};
struct segtree {
    vector<data> nodes;
    vector<int> posToDist;
    vector<bool> vis;
    int n;
    segtree(int _n, vector<int>& _posToDist) {
        n = _n;
        nodes.resize(4 * n);
        posToDist = _posToDist;
        vis.resize(n);
        build(1, 0, n - 1);
    }
    data merge(data& l, data& r, int l1, int r1, int l2, int r2) {
        data res;
        if (l1 == r1 && l2 == r2) {
            int dist = posToDist[l2] - posToDist[r1];
            res.pref = dist;
            res.suf = dist;
            res.mx = dist;
        } else {
            int lrDist = posToDist[l2] - posToDist[r1];
            res.pref = l.pref;
            if (posToDist[r1] - posToDist[l1] == l.pref) {
                if (!vis[r1]) {
                    res.pref += lrDist;
                    if (!vis[l2]) res.pref += r.pref;
                }
            }
            res.suf = r.suf;
            if (posToDist[r2] - posToDist[l2] == r.suf) {
                if (!vis[l2]) {
                    res.suf += lrDist;
                    if (!vis[r1]) res.suf += l.suf;
                }
            }
            res.mx = max(l.mx, r.mx);
            if (!vis[r1] && !vis[l2]) {
                res.mx = max(res.mx, l.suf + lrDist + r.pref);
            } else if (!vis[r1]) {
                res.mx = max(res.mx, l.suf + lrDist);
            } else if (!vis[l2]) {
                res.mx = max(res.mx, r.pref + lrDist);
            }
            res.mx = max(res.mx, lrDist);
        }
        return res;
    }
    Ret mergeRet(Ret &l, Ret &r) {
        if (l.L == -1) return r;
        if (r.L == -1) return l;
        return {merge(l.val, r.val, l.L, l.R, r.L, r.R), l.L, r.R};
    }
    void build(int idx, int s, int e) {
        if (s == e) {
            nodes[idx] = data{0, 0, 0};
            return;
        }
        int m = (s + e) / 2;
        build(2 * idx, s, m);
        build(2 * idx + 1, m + 1, e);
        nodes[idx] = merge(nodes[2 * idx], nodes[2 * idx + 1], s, m, m + 1, e);
    }
    void update(int idx, int s, int e, int pos) {
        if (s == e) {
            nodes[idx] = data{0, 0, 0};
            vis[s] = 1;
            return;
        }
        int m = (s + e) / 2;
        if (pos <= m)
            update(2 * idx, s, m, pos);
        else
            update(2 * idx + 1, m + 1, e, pos);
        nodes[idx] = merge(nodes[2 * idx], nodes[2 * idx + 1], s, m, m + 1, e);
    }
    Ret query(int idx, int s, int e, int l, int r) {
        if (s > r || l > e || s > e || l > r)
            return Ret{{0, 0, 0}, -1, -1};
        if (l <= s && e <= r)
            return Ret{nodes[idx], s, e};
        int m = (s + e) / 2;
        Ret lans = query(2 * idx, s, m, l, r);
        Ret rans = query(2 * idx + 1, m + 1, e, l, r);
        return mergeRet(lans, rans);
    }
};
class Solution {
public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        int n = queries.size();
        vector<int> tmp;
        tmp.push_back(0);
        for (auto& q : queries) {
            if (q[0] == 1) {
                tmp.push_back(q[1]);
            } else {
                tmp.push_back(q[1]);
            }
        }
        sort(tmp.begin(), tmp.end());
        tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());

        int sz = tmp.size();
        vector<int> posToDist(sz);
        unordered_map<int, int> distToPos;
        for (int i = 0; i < int(tmp.size()); i++) {
            posToDist[i] = tmp[i];
            distToPos[tmp[i]] = i;
        }

        segtree tree(sz, posToDist);
        vector<bool> ans;
        for (auto& q : queries) {
            if (q[0] == 1) {
                tree.update(1, 0, sz - 1, distToPos[q[1]]);
            } else {
                Ret res = tree.query(1, 0, sz - 1, 0, distToPos[q[1]]);
                ans.push_back(res.val.mx >= q[2]);
            }
        }
        return ans;
    }
};