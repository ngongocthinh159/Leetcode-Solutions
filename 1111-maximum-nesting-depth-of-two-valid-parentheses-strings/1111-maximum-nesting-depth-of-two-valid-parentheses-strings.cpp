class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        int level = 0;
        int n = seq.size();
        vector<int> l(n);
        vector<int> toRight(n);
        vector<int> st;
        for (int i = 0; i < n; i++) {
            if (seq[i] == '(') level++, st.push_back(i);
            l[i] = level;
            if (seq[i] == ')') level--, toRight[st.back()] = i, st.pop_back();
        }
        vector<int> ans(n);
        for (int i = 0; i < n; ) {
            int start = i;
            int end = toRight[i];
            
            int mx = *max_element(l.begin() + start, l.begin() + end + 1);
            int half = (mx + 2 - 1) / 2;
            for (int j = start; j <= end; j++) {
                if (l[j] <= half) ans[j] = 0;
                else ans[j] = 1;
            }

            i = toRight[i] + 1;
        }
        return ans;
    }
};