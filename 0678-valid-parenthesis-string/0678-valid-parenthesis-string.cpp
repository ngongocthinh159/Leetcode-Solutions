class Solution {
public:
    bool checkValidString(string s) {
        int n = s.size();
        vector<int> st;
        deque<int> q;
        for (int i = 0; i < n; i++) {
            if (s[i] == '*') q.push_back(i);
            else if (s[i] == '(') {
                st.push_back(i);
            } else {
                if (st.size()) {
                    st.pop_back();
                } else {
                    if (q.empty()) return false;
                    q.pop_front();
                }
            }
        }
        for (int i = 0, j = 0; i < int(st.size()); i++) {
            while (j < q.size() && q[j] < st[i]) j++;
            if (j == q.size()) return false;
            j++;
        }
        return true;
    }
};