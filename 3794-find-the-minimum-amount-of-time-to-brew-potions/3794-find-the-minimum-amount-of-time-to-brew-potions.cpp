class Solution {
public:
    long long minTime(vector<int>& skill, vector<int>& mana) {
        int n = skill.size(), m = mana.size();
        long long sum = 0;
        for (auto x : skill) sum += x * mana[0];
        long long S = 0;
        long long ans = sum;
        for (int i = 1; i < m; i++) {
            long long T = 0;
            long long prefS = S + skill[0] * mana[i - 1];
            long long prefT = 0;

            for (int j = 0; j < n; j++) {
                T = max(T, prefS - prefT);
                if (j + 1 < n)
                    prefS += 1LL * skill[j + 1] * mana[i - 1];
                prefT += skill[j] * mana[i];
            }
            // cout << i << ' ' << T << '\n';

            S = T;
            ans = T + prefT;
        }
        return ans;
    }
};