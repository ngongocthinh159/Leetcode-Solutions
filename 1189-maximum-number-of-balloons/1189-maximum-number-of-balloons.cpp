class Solution {
public:
    int maxNumberOfBalloons(string text) {
        string pattern = "balloon";
        int cnt[26]{}, f[26]{};
        for (auto c : pattern) cnt[c - 'a']++;
        int mn = INT_MAX;
        for (auto c : text) f[c - 'a']++;
        for (int i = 0; i < 26; i++) if (cnt[i]) {
            mn = min(mn, f[i] / cnt[i]);
        }
        return mn;
    }
};