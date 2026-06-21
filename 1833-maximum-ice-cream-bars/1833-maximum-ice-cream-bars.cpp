#define N 100005
int cnt[N];
class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        int ans = 0;
        for (auto &c : costs) cnt[c]++;
        for (int i = 1; i < N; i++) if (cnt[i]) {
            int will = min(cnt[i], coins/i);
            if (will == 0) break;
            ans += will;
            coins -= will * i;
        }
        for (auto &c : costs) cnt[c]--;
        return ans;
    }
};