#define ll long long
struct node {
    ll sum;
    int idx;
    node* prev;
    node* nxt;
    node(ll _sum, int _idx) {
        sum = _sum, idx = _idx, prev = nxt = nullptr;
    }
};
struct P {
    node* cur;
    node* nxt;
    P(node* _cur, node* _nxt) : cur(_cur), nxt(_nxt) {}
};
ll sumP(const P &p) {
    return p.cur->sum + p.nxt->sum;
}
int idxP(const P &p) {
    return p.cur->idx;
}
class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size(), cnt = 0, ans = 0;
        auto Cmp = [](auto &p1, auto &p2) {
            if (sumP(p1) < sumP(p2)) return true;
            if (sumP(p1) == sumP(p2) && idxP(p1) < idxP(p2)) return true;
            return false;
        };
        set<P, decltype(Cmp)> S;
        node* prev = new node{nums[0], 0};
        node* root = prev;
        for (int i = 1; i < n; i++) {
            if (nums[i] < nums[i - 1]) cnt++;
            node* cur = new node{nums[i], i};
            cur->prev = prev;
            prev->nxt = cur;
            S.insert({prev, cur});
            prev = cur;
        }
        unordered_set<node*> merged;
        bool f = false;
        while (S.size() && cnt) {
            auto p = *S.begin();
            auto cur = p.cur;
            auto nxt = p.nxt; 
            S.erase(S.begin());
            if (merged.count(cur) || merged.count(nxt)) continue;
            merged.insert(cur);
            merged.insert(nxt);

            ans++;

            if (cur->sum > nxt->sum) cnt--;
            node* prv = cur->prev;
            node* nnxt = nxt->nxt;
            node* inserted = new node{sumP(p), idxP(p)};
            if (prv != nullptr) {
                prv->nxt = inserted;
                inserted->prev = prv;
                if (prv->sum > inserted->sum) cnt++;
                if (prv->sum > cur->sum) cnt--;
                S.erase(P{prv, inserted});
                S.insert(P{prv, inserted});
            }
            if (nnxt != nullptr) {
                nnxt->prev = inserted;
                inserted->nxt = nnxt;   
                if (inserted->sum > nnxt->sum) cnt++;
                if (nxt->sum > nnxt->sum) cnt--;
                S.erase(P{inserted, nnxt});
                S.insert(P{inserted, nnxt});
            }
        }
        return ans;
    }
};