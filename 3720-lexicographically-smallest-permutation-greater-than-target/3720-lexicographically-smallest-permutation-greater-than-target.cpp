class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int cnt[26]{};
        int n = s.size();
        for (auto c : s) cnt[c - 'a']++;
        int idx = -1;
        for (int i = 0; i < n; i++) {
            int c = target[i] - 'a';
            bool ok = false;
            for (int j = c + 1; j < 26; j++) if (cnt[j]) {
                ok = true;
                break;
            }
            if (ok) idx = i;
            if (!cnt[c]) break;
            cnt[c]--;
        }
        if (idx == -1) return "";
        int f[26]{};
        for (auto c : s) f[c - 'a']++;
        string t = "";
        for (int i = 0; i < idx; i++) t += target[i], f[target[i] - 'a']--;
        for (int j = target[idx] - 'a' + 1; j < 26; j++) if (f[j]) {
            t += j + 'a';
            f[j]--;
            break;
        }
        for (int i = 0; i < 26; i++) if (f[i]) {
            for (int j = 0; j < f[i]; j++) t += i + 'a';
        }
        return t;
    }
};