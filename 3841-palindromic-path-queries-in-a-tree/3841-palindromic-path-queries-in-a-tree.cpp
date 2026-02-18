struct segtree {
    vector<int> nodes;
    int n;
    segtree(vector<int> &arr) {
        n = arr.size();
        nodes.resize(4*n);
        build(1, 0, n - 1, arr);
    }
    int merge(const int &l, const int &r) {
        return l ^ r;
    }
    void build(int idx, int s, int e, vector<int> &arr) {
        if (s == e) {
            nodes[idx] = arr[s];
            return;
        }
        int m = (s + e)/2;
        build(2*idx, s, m, arr);
        build(2*idx + 1, m + 1, e, arr);
        nodes[idx] = merge(nodes[2*idx], nodes[2*idx + 1]);
    }
    void update(int idx, int s, int e, int pos, int val) {
        if (s == e) {
            nodes[idx] ^= val;
            return;
        }
        int m = (s + e)/2;
        if (pos <= m)
            update(2*idx, s, m, pos, val);
        else
            update(2*idx + 1, m + 1, e, pos, val);
        nodes[idx] = merge(nodes[2*idx], nodes[2*idx + 1]);
    }
    int query(int idx, int s, int e, int l, int r) {
        if (s > r || l > e || s > e || l > r) return 0;
        if (l <= s && e <= r) return nodes[idx];
        int m = (s + e)/2;
        return merge(query(2*idx, s, m, l, r), query(2*idx + 1, m + 1, e, l, r));
    }
};
class Solution {
public:
    vector<vector<int>> g;
    string t;
    vector<int> big, child, chain, euler, pos, par, depth;
    int T = 0, N;
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        g.resize(n + 1);
        big.resize(n + 1);
        child.resize(n + 1);
        chain.resize(n + 1);
        euler.resize(n + 1);
        pos.resize(n + 1);
        par.resize(n + 1);
        depth.resize(n + 1);
        N = n + 1;

        t = "#" + s;
        for (auto &e : edges) {
            g[e[0] + 1].push_back(e[1] + 1);
            g[e[1] + 1].push_back(e[0] + 1);
        }
        dfs1(1, 0);
        dfs2(1, 0, 1);

        segtree tree(euler);

        vector<bool> ans;
        string type;
        int u, v;
        char c;
        for (auto &q : queries) {
            stringstream ss(q);
            ss >> type;
            if (type[0] == 'u') {
                ss >> u >> c;
                u++;
                int delta = (1 << (t[u] - 'a')) ^ (1 << (c - 'a'));
                tree.update(1, 0, N - 1, pos[u], delta);
                t[u] = c;

            } else {
                ss >> u >> v;
                u++, v++;
                if (__builtin_popcount(query(u, v, tree)) <= 1)
                    ans.push_back(true);
                else
                    ans.push_back(false);

            }
        } 
        return ans;
    }
    int query(int u, int v, segtree &tree) {
        int res = 0;
        while (chain[u] != chain[v]) {
            if (depth[chain[u]] < depth[chain[v]]) swap(u, v);
            res ^= tree.query(1, 0, N - 1, pos[chain[u]], pos[u]);
            u = par[chain[u]];
        }
        if (depth[u] < depth[v]) swap(u, v);
        res ^= tree.query(1, 0, N - 1, pos[v], pos[u]);
        return res;
    }
    void dfs2(int u, int p, int cur_chain) {
        pos[u] = T;
        chain[u] = cur_chain;
        euler[T++] = (1 << (t[u] - 'a')); 

        if (big[u] != 0) 
            dfs2(big[u], u, cur_chain);

        for (auto v : g[u]) if (v != p && v != big[u])
            dfs2(v, u, v);
    }
    void dfs1(int u, int p) {
        child[u] = 1;
        big[u] = 0;
        int mx = -1;
        for (auto v : g[u]) if (v != p) {
            par[v] = u;
            depth[v] = depth[u] + 1;
            dfs1(v, u);
            child[u] += child[v];
            if (mx < child[v]) {
                mx = child[v];
                big[u] = v;
            }
        }
    }
};