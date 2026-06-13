class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        unordered_map<int,int> f;
        vector<int> fact;
        int mnPrice = 1e9 + 5;
        for (auto &item : items) {
            fact.push_back(item[0]), f[item[0]]++;
            mnPrice = min(mnPrice, item[1]);
        }
        sort(fact.begin(), fact.end());
        fact.erase(unique(fact.begin(), fact.end()), fact.end());
        vector<int> multipleCnt(n + 1);
        for (int i = 0; i < int(fact.size()); i++) {
            int curFact = fact[i];
            for (int j = curFact; j <= n; j += curFact) multipleCnt[curFact] += f[j];
        }
        vector<pair<int,int>> v;
        for (auto &item : items) {
            int can = multipleCnt[item[0]] - 1;
            v.push_back({item[1], can});
        }
        sort(v.begin(), v.end(), [](auto &p1, auto &p2){
            return p1.first < p2.first;
        });
        int ans = 0;
        for (int i = 0; i < int(v.size()); i++) {
            if (2 * mnPrice <= v[i].first) break;
            int will = min(budget / v[i].first, v[i].second);
            ans += will * 2;
            budget -= v[i].first * will;
        }
        int will = budget / mnPrice;
        ans += will;
        return ans;
    }   
};