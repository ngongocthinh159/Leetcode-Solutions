#define ll long long
using It = list<tuple<ll,int>>::iterator;
struct P {
    It it;
    It nit;
};
struct cmp {
    bool operator() (P const&a, P const&b) const {
        if (get<0>(*a.it) + get<0>(*a.nit) < get<0>(*b.it) + get<0>(*b.nit)) return true;
        if ((get<0>(*a.it) + get<0>(*a.nit) == get<0>(*b.it) + get<0>(*b.nit)) &&
            get<1>(*a.it) < get<1>(*b.it)) return true;
        return false;
    };
};
class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();
        list<tuple<ll,int>> ml;
        set<P, cmp> S;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            auto it = ml.insert(ml.end(), {nums[i], i});
            if (i > 0) {
                S.insert(P{prev(it), it});
                if (nums[i] < nums[i -1]) cnt++;
            }
        }
        if (!cnt) return 0;
        int ans = 0;
        while (S.size() && cnt) {
            ans++;
            auto p = *S.begin();
            auto it = p.it;
            auto nit = p.nit;
            S.erase(S.begin());
            if (get<0>(*it) > get<0>(*nit)) cnt--;
            
            auto nnit = next(nit);
            auto pit = it != ml.begin() ? prev(it) : ml.end();

            if (nnit != ml.end()) {
                S.erase({nit, nnit});
                if (get<0>(*nit) > get<0>(*nnit)) cnt--;
            }
            if (pit != ml.end()) {
                S.erase({pit, it});
                if (get<0>(*pit) > get<0>(*it)) cnt--;
            }
            
            auto insert_it = ml.insert(nnit, {get<0>(*it) + get<0>(*nit), get<1>(*it)});
            ml.erase(it);
            ml.erase(nit);
            if (nnit != ml.end()) {
                S.insert(P{insert_it, nnit});
                if (get<0>(*insert_it) > get<0>(*nnit)) cnt++;
            }
            if (pit != ml.end()) {
                S.insert(P{pit, insert_it});
                if (get<0>(*pit) > get<0>(*insert_it)) cnt++;
            }
        }
        return ans;
    }
};