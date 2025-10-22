#define LOG 18
#define N 100005
int rmqmn[LOG + 1][N];
int rmqmx[LOG + 1][N];
class Solution {
public:
    int queryMx(int l, int r) {
        int msb = 32 - __builtin_clz(r - l + 1) - 1;
        return max(rmqmx[msb][l], rmqmx[msb][r - (1 << msb) + 1]);
    }
    int queryMn(int l, int r) {
        int msb = 32 - __builtin_clz(r - l + 1) - 1;
        return min(rmqmn[msb][l], rmqmn[msb][r - (1 << msb) + 1]);
    }
    long long maxTotalValue(vector<int>& nums, int k) {
        int n = nums.size();

        for (int i = 0; i < n; i++) rmqmx[0][i] = rmqmn[0][i] = nums[i];
        for (int j = 1; j <= LOG; j++)
            for (int i = 0; i + (1 << j) - 1 < n; i++)
                rmqmx[j][i] = max(rmqmx[j - 1][i], rmqmx[j - 1][i + (1 << (j - 1))]);
        for (int j = 1; j <= LOG; j++)
            for (int i = 0; i + (1 << j) - 1 < n; i++)
                rmqmn[j][i] = min(rmqmn[j - 1][i], rmqmn[j - 1][i + (1 << (j - 1))]);

        auto cmp = [&](auto &p1, auto &p2) {
            return queryMx(p2.first, p2.second) - queryMn(p2.first, p2.second) >
                    queryMx(p1.first, p1.second) - queryMn(p1.first, p1.second);
        };
        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> q(cmp);
        unordered_set<long long> S;
        q.push({0, n - 1});
        long long base = n + 5;
        S.insert(1 + (n - 1 + 1) * base);
        long long ans = 0;
        while (k--) {
            auto p = q.top(); q.pop();
            int l = p.first;
            int r = p.second;
            ans += queryMx(l, r) - queryMn(l, r);
            if (l + 1 <= r && !S.count(l + 2 + (r + 1) * base)) q.push({l + 1, r}), S.insert(l + 2 + (r + 1) * base);
            if (l <= r - 1 && !S.count(l + 1 + r * base)) q.push({l, r - 1}), S.insert(l + 1 + r * base);
        }
        return ans;
    }
};