class Solution {
public:
    void reduce(vector<pair<char,int>> &st, int k) {
        while (st.size() >= 2 && st.back().first == ')' && st.back().second == k && st[st.size() - 2].first == '(' && st[st.size() - 2].second >= k) {
            st.pop_back();
            st.back().second -= k;
            if (st.back().second == 0) st.pop_back();
        }
    }
    string removeSubstring(string s, int k) {
        int n = s.size();
        vector<pair<char,int>> st;
        string res = "";
        for (int i = 0; i < n; i++) {
            char c = s[i];
            if (st.size() && st.back().first == c) {
                st.back().second++;
            } else
                st.push_back({c, 1});
            reduce(st, k);
        }
        for (int i = 0; i < st.size(); i++)
            for (int j = 0; j < st[i].second; j++) res += st[i].first;
        return res;
    }
};