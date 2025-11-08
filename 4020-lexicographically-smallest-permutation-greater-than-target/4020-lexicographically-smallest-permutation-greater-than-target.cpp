class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();
        vector<int> cnt(26);
        for (auto c : s) cnt[c -'a']++;
        auto cnt2 = cnt;
        int idx = -1, cc = -1;
        for (int i = 0; i < n; i++) {
            int cur = target[i] - 'a';
            int fi = -1;
            for (int j = cur + 1; j < 26; j++) if (cnt[j]) {
                fi = j;
                break;
            }
            if (fi != -1)
                idx = i, cc = fi;
            if (!cnt[cur]) break;
            cnt[cur]--;
        }
        if (idx == -1) return "";
        string res = "";
        for (int i = 0; i < idx; i++) {
            res += target[i];
            cnt2[target[i] - 'a']--;
        }
        res += cc + 'a';
        cnt2[cc]--;
        string tmp = "";
        for (int i = 0; i < 26; i++) 
            for (int j = 0; j < cnt2[i]; j++) tmp += 'a' + i;
        res += tmp;
        return res;
    }
};