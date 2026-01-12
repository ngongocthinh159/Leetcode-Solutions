class Solution {
public:
    int maxRec(vector<int> &h) {
        int n = h.size();
        vector<int> left(n);
        vector<int> right(n);
        stack<int> S;
        for (int i = 0; i < n; i++) {
            while (S.size() && !(h[S.top()] < h[i])) S.pop();
            if (S.size()) left[i] = S.top();
            else left[i] = -1;
            S.push(i);
        }
        while (S.size()) S.pop();
        int ans = INT_MIN;
        for (int i = n - 1; i >= 0; i--) {
            while (S.size() && !(h[S.top()] < h[i])) S.pop();
            if (S.size()) right[i] = S.top();
            else right[i] = n;
            ans = max((right[i] - left[i] - 1)*h[i], ans);
            S.push(i);
        }
        return ans;
    }
    int maximalRectangle(vector<vector<char>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<int> h(m);
        int ans = INT_MIN;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] == '1') h[j] = i == 0 ? 1 : 1 + h[j];
                else h[j] = 0;
            }
            ans = max(ans, maxRec(h));
        }
        return ans;
    }
};