class Solution {
public:
    int comb(int n, int r, int k) {
        r = min(r, n - r);
        long long res = 1;
        for (int i = 1; i <= r; i++) {
            res = res * (n - i + 1) / i;
            if (res > k) return k + 1;
        }
        return res;
    }
    string smallestPalindrome(string s, int k) {
        string t = "";
        string center = "";
        int cnt[26]{};
        for (auto c : s) cnt[c - 'a']++;
        for (int i = 0; i < 26; i++) if (cnt[i] & 1) center += i + 'a', cnt[i]--;
        int tot = 0;
        for (int i = 0; i < 26; i++) cnt[i] /= 2, tot += cnt[i];

        while (tot--) {
            bool found = false;
            for (int i = 0; i < 26; i++) if (cnt[i]) {
                cnt[i]--;

                int totCnt = tot;
                long long perm = 1;
                bool kSmallerEqual = false;
                if (k <= perm) 
                    kSmallerEqual = true;
                else {
                    for (int j = 0; j < 26; j++) if (cnt[j]) {
                        int res = comb(totCnt, cnt[j], k);
                        totCnt -= cnt[j];
                        perm = perm * res;
                        if (perm >= k) {
                            kSmallerEqual = true;
                            break;
                        }
                    }
                }

                if (kSmallerEqual) {
                    found = true;
                    t += i + 'a';
                    break;
                } else {
                    k -= perm;
                    cnt[i]++;
                }
            }
            if (!found) return "";
        }
        string r = t;
        reverse(r.begin(), r.end());
        return t + center + r;
    }
};