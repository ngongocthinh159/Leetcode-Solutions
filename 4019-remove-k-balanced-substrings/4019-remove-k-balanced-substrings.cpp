class Solution {
public:
    void reduce(vector<pair<char,int>> &st, int k) {
        while (st.size() >= 2 && st.back().first == ')' && st.back().second >= k && st[st.size() - 2].first == '(' && st[st.size() - 2].second >= k) {
            st.back().second -= k;
            st[st.size() - 2].second -= k;
            if (st[st.size() - 2].second == 0) swap(st[st.size() - 2], st[st.size() - 1]), st.pop_back();
            if (st.back().second == 0) st.pop_back();
            while (st.size() >= 2 && st.back().first == st[st.size() - 2].first) {
                st[st.size() - 2].second += st.back().second;
                st.pop_back();
            }
        }
    }
    string removeSubstring(string s, int k) {
        int n = s.size();
        vector<pair<char,int>> st;
        string res = "";
        for (int i = 0; i < n; ) {
            char c = s[i];
            int cnt = 0;
            while (i < n && c == s[i]) i++, cnt++;
            if (st.size() && st.back().first == c) {
                st.back().second += cnt;
            } else
                st.push_back({c, cnt});
            reduce(st, k);
        }
        for (int i = 0; i < st.size(); i++)
            for (int j = 0; j < st[i].second; j++) res += st[i].first;
        return res;
    }
};