class Solution {
public:
    vector<vector<int>> highestPeak(vector<vector<int>>& w) {
        int n = w.size();
        int m = w[0].size();
        vector<vector<int>> dist(n, vector<int>(m, 1e9));
        deque<pair<int,int>> q;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) if (w[i][j] == 1) {
                dist[i][j] = 0;
                q.push_front({i, j});
            }
        vector<vector<int>> moves = {{0,1},{1,0},{0,-1},{-1,0}};
        int cur = 1;
        while (q.size()) {
            for (int sz = q.size(); sz; sz--) {
                auto [i, j] = q.back();
                q.pop_back();
                for (auto &move : moves) {
                    int I = move[0] + i;
                    int J = move[1] + j;
                    if (0 <= I && I < n && 0 <= J && J < m) {
                        if (dist[I][J] == 1e9) {
                            dist[I][J] = cur;
                            q.push_front({I, J});
                        }
                    }
                }
            }
            cur++;
        }
        return dist;
    }
};