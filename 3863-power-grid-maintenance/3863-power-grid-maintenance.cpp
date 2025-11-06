class Solution {
public:
    vector<vector<int>> g;
    vector<bool> vis;
    unordered_map<int,int> nodeToCompo;
    unordered_map<int,set<int>> compoToList;
    void dfs(int u, int id) {
        nodeToCompo[u] = id;
        compoToList[id].insert(u);
        vis[u] = 1;
        for (auto v : g[u]) if (!vis[v]) {
            dfs(v, id);
        }
    }
    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {
        g.assign(c + 1, vector<int>());
        vis.assign(c + 1, false);
        for (auto &p : connections) {
            g[p[0]].push_back(p[1]);
            g[p[1]].push_back(p[0]);
        }
        int id = 0;
        for (int i = 1; i <= c; i++) if (!vis[i]) {
            dfs(i, id);
            id++;
        }
        vector<int> ans;
        for (auto &q : queries) {
            if (q[0] == 1) {
                int cid = nodeToCompo[q[1]];
                if (compoToList[cid].size()) {
                    if (compoToList[cid].count(q[1]))
                        ans.push_back(q[1]);
                    else
                        ans.push_back(*(compoToList[cid].begin()));
                }
                else {
                    ans.push_back(-1);   
                }
            } else {
                compoToList[nodeToCompo[q[1]]].erase(q[1]);
            }
        }
        return ans;
    }
};