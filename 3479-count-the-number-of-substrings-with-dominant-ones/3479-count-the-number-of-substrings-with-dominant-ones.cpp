class Solution {
public:
    int numberOfSubstrings(string s) {
        int n = s.size();
        int sq = sqrt(n);
        int ans = 0;
        for (int z = 0; z <= sq; z++) {
            int cnt1 = 0, cnt2 = 0;
            for (int i = 0, l1 = 0, l2 = 0; i < n; i++) {
                if (s[i] == '0') cnt1++, cnt2++;
                while (l1 <= i && cnt1 > z) if (s[l1++] == '0') cnt1--;
                while (l2 <= i && cnt2 >= z) if (s[l2++] == '0') cnt2--;
                int can = l2 - l1;
                if (can >= 1) {
                    int minLen = z * z + z;
                    int k = i - minLen + 1;
                    int st = l1, end = l2 - 1;
                    if (k > end) ans += end - st + 1;
                    else if (st <= k && k <= end) ans += k - st + 1; 
                }
            }
        }
        return ans;
    }
};