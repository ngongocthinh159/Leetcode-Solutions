struct myds {
    set<pair<int,int>> top;
    set<pair<int,int>> bot;
    long long sumTop = 0, sumBot = 0;
    int k;
    myds(int _k) : k(_k) {}

    void reconcile() {
        while (bot.size() && top.size() && top.begin()->first < bot.rbegin()->first) {
            auto pbot = *bot.rbegin();
            auto ptop = *top.begin();
            
            bot.erase(pbot);
            sumBot -= pbot.first;
            top.erase(ptop);
            sumTop -= ptop.first;

            bot.insert(ptop);
            sumBot += ptop.first;
            top.insert(pbot);
            sumTop += pbot.first;
        }
        while (top.size() && bot.size() < k) {
            auto ptop = *top.begin();
            top.erase(ptop);
            sumTop -= ptop.first;
            bot.insert(ptop);
            sumBot += ptop.first;
        }
        while (bot.size() > k) {
            auto pbot = *bot.rbegin();
            bot.erase(pbot);
            sumBot -= pbot.first;
            top.insert(pbot);
            sumTop += pbot.first;
        }
    }
    void insert(const pair<int,int> &p) {
        bot.insert(p);
        sumBot += p.first;
        reconcile();
    }  
    void remove(const pair<int,int> &p) {
        if (top.erase(p)) sumTop -= p.first;
        if (bot.erase(p)) sumBot -= p.first;
        reconcile();
    }
    long long query() {
        return sumBot;
    }
};
class Solution {
public:

    long long minimumCost(vector<int>& nums, int k, int dist) {
        int n = nums.size();
        dist++;
        long long ans = 1e18 + 5;
        myds q(k - 1);
        for (int i = 1; i <= min(n - 1, dist); i++) q.insert({nums[i], i});
        ans = min(ans, nums[0] + q.query());
        for (int i = dist + 1; i < n; i++) {
            int l = i - dist + 1;
            q.remove({nums[l - 1], l - 1});
            q.insert({nums[i], i});
            ans = min(ans, nums[0] + q.query());
        }
        return ans;
    }
};