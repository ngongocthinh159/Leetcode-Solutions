class Solution {
public:
    int minGenerations(vector<vector<int>>& points, vector<int>& target) {
        int n = points.size();
        set<vector<int>> S;
        for (auto &p : points) {
            S.insert(p);
            if (p == target) return 0;
        }
        int level = 0;
        int k = 0;
        while (1) {
            bool f = false;
            int sz = points.size();
            if (k == 0) {
                for (int j = 1; j < sz; j++)
                    for (int i = 0; i < j; i++) {
                        vector<int> np = {(points[i][0] + points[j][0])/2,
                                    (points[i][1] + points[j][1])/2,
                                    (points[i][2] + points[j][2])/2};
                        if (!S.count(np)) {
                            S.insert(np);
                            points.push_back(np);
                            f = true;
                        }
                    }
                k = sz;
            } else {
                for (int j = k; j < sz; j++) {
                    if (points[j] == target) return level;
                    for (int i = 0; i < j; i++) {
                        vector<int> np = {(points[i][0] + points[j][0])/2,
                                    (points[i][1] + points[j][1])/2,
                                    (points[i][2] + points[j][2])/2};
                        if (!S.count(np)) {
                            S.insert(np);
                            points.push_back(np);
                            f = true;
                        }
                    }
                }
                k = sz;
            }
            level++;
            if (!f) break;
        }
        return -1;
    }
};