class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        vector<pair<int,int>> v;
        int cnt1 = 0;
        int n = s.size();
        {
            int i = 0;
            while (i < n) {
                char c = s[i];
                int cnt = 0;
                while (i < n && c == s[i]) {
                    cnt++;
                    i++;
                }
                if (c == '1') cnt1 += cnt;
                v.push_back({c - '0', cnt});
            }
        }
        int mx0 = -1;
        int mnRun1 = INT_MAX;
        int mxRun0 = -1;
        for (int i = 0; i < v.size(); i++) {
            if (i != 0 && i != int(v.size()) - 1 && v[i].first == 1) {
                mx0 = max(mx0, v[i - 1].second + v[i + 1].second);
                mnRun1 = min(mnRun1, v[i].second);
            }
            if (v[i].first == 0) mxRun0 = max(mxRun0, v[i].second);
        }

        int ans = cnt1;
        if (mx0 != -1) ans = max(ans, cnt1 + mx0);
        if (mnRun1 != INT_MAX && mxRun0 != -1) {
            ans = max(ans, cnt1 - mnRun1 + mxRun0);
        }
        return ans;
    }
};