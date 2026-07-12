class Solution {
public:
    int countLatticePoints(vector<vector<int>>& circles) {
        unordered_set<long long> S;
        vector<array<int,2>> moves = {{1,0},{0,1},{-1,0},{0,-1}};
        for (auto &c : circles) {
            int d = c[2];
            int x = c[0];
            int y = c[1];
            for (int i = x - d; i <= x + d; i++)
                for (int j = y - d; j <= y + d; j++) if ((i - x) * (i - x) + (j - y) * (j - y) <= d * d) S.insert(i * 1e5 + j);
        }
        return S.size();
    }
};