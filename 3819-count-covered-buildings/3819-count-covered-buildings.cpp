class Solution {
public:
    int countCoveredBuildings(int n, vector<vector<int>>& buildings) {
        int ans = 0;
        unordered_map<int,pair<int,int>> xtomnmx;
        unordered_map<int,pair<int,int>> ytomnmx;
        for (auto &b : buildings) {
            int x = b[0];
            int y = b[1];
            if (!xtomnmx.count(x)) {
                xtomnmx[x] = {y, y};
            }
            xtomnmx[x].first = min(xtomnmx[x].first, y);
            xtomnmx[x].second = max(xtomnmx[x].second, y);
            if (!ytomnmx.count(y)) {
                ytomnmx[y] = {x, x};
            }
            ytomnmx[y].first = min(ytomnmx[y].first, x); 
            ytomnmx[y].second = max(ytomnmx[y].second, x); 
        }
        for (auto & b : buildings) {
            int x = b[0];
            int y = b[1];
            if (xtomnmx[x].first < y && y < xtomnmx[x].second && ytomnmx[y].first < x && x < ytomnmx[y].second) ans++;
        }

        return ans;
    }
};