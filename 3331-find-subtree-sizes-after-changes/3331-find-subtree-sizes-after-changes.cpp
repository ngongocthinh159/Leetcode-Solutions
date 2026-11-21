class Solution {
public:
    vector<vector<int>> charToList;
    vector<int> childcnt;
    vector<bool> remove;
    vector<array<int,2>> edges;
    vector<array<int,2>> newEdges;
    vector<vector<int>> g, g2;
    int n;
    void dfs(int u, int puIdx, string& s) {
        if (charToList[s[u] - 'a'].size()) {
            if (charToList[s[u] - 'a'].back() != edges[puIdx][0]) {
                remove[puIdx] = true;
                newEdges.push_back({charToList[s[u] - 'a'].back(), u});
            }
        }
        charToList[s[u] - 'a'].push_back(u);
        for (auto uvIdx : g[u]) {
            int v = edges[uvIdx][1];
            dfs(v, uvIdx, s);
        }
        charToList[s[u] - 'a'].pop_back();
    }
    void dfs2(int u) {
        cout << u << endl;
        childcnt[u] = 1;
        for (auto v : g2[u]) dfs2(v), childcnt[u] += childcnt[v];
    }
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        n = parent.size();
        g.resize(n);
        g2.resize(n);
        childcnt.resize(n);
        charToList.resize(26);
        remove.assign(n - 1, false);
        for (int i = 1; i < n; ++i) {
            edges.push_back({parent[i], i});
            g[parent[i]].push_back(int(edges.size()) - 1);
        }
        dfs(0, -1, s);
        for (int i = 0; i < int(edges.size()); ++i) if (!remove[i]) {
            g2[edges[i][0]].push_back(edges[i][1]);
        }
        for (int i = 0; i < int(newEdges.size()); ++i) {
            g2[newEdges[i][0]].push_back(newEdges[i][1]);
        }
        dfs2(0);
        return childcnt;
    }
};