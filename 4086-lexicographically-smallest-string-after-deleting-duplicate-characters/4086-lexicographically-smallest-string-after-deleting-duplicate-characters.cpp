class Solution {
public:
    string lexSmallestAfterDeletion(string s) {
        s += 'a' - 1;
        int n = s.size();
        unordered_map<char,int> f;
        for (auto c : s) f[c]++;
        vector<char> st;
        int i = 0;
        while (i < n) {
            while (st.size() && st.back() > s[i] && f[st.back()] >= 2) {
                f[st.back()]--;
                st.pop_back();
            }
            st.push_back(s[i++]);
        }
        string res = "";
        for (int i = 0; i < st.size() - 1; i++) res += st[i];
        return res;
    }
};