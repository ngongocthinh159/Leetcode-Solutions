class Solution {
public:
    int countLatticePoints(vector<vector<int>>& circles) {
        unordered_set<long long> S;
        vector<array<int,2>> moves = {{1,0},{0,1},{-1,0},{0,-1}};
        for (auto &c : circles) {
            int d = c[2];
            unordered_set<long long> vis;
            deque<array<int,2>> q;
            q.push_front({c[0], c[1]});
            vis.insert(c[0] * 1e5 + c[1]);
            while (q.size()) {
                for (int sz = q.size(); sz; sz--) {
                    auto [i, j] = q.back();
                    S.insert(i * 1e5 + j);
                    q.pop_back();
                    for (auto &move : moves) {
                        int I = i + move[0];
                        int J = j + move[1];
                        int D = (I - c[0]) * (I - c[0]) + (J - c[1]) * (J - c[1]);
                        long long x = I * 1e5 + J;
                        if (D <= d * d && !vis.count(x)) {
                            vis.insert(x);
                            q.push_front({I, J});
                        }
                    }
                }
            }
        }
        return S.size();
    }
};