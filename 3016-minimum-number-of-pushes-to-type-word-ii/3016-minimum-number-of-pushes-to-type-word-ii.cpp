class Solution {
public:
    int minimumPushes(string word) {
        int n = word.size();
        int cnt[26]{};
        for (auto c : word) cnt[c - 'a']++;
        vector<int> v; 
        for (int i =0 ; i < 26; i++) if (cnt[i]) v.push_back(cnt[i]);
        sort(v.begin(), v.end());
        int ans = 0;
        for (int i = int(v.size()) - 1, cnt = 8, cost = 1; i >= 0; i--) {
            ans += cost * v[i];

            cnt--;
            if (cnt == 0) cnt = 8, cost++;
        }
        return ans;
    }
};