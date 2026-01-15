class Solution {
public:
    int findmax(vector<int> &hs) {
        sort(hs.begin(), hs.end());
        int n = hs.size(), mxh = 0;
        for (int i = 0; i < n;) {
            int cnt = 1;
            int s = hs[i];
            while (i + 1 < n && hs[i + 1] - hs[i] == 1) {
                cnt++;
                i++;
            }
            mxh = max(mxh, cnt);
            i++;
        }
        return mxh + 1;
    }
    int maximizeSquareHoleArea(int n, int m, vector<int>& hs, vector<int>& vs) {
        int e = min(findmax(hs), findmax(vs));
        return e * e;
    }
};