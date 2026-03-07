class Solution {
public:
    long long countSubarrays(vector<int>& a, int k, int m) {
        int n = a.size();
        list<int> ls; // list index
        unordered_map<int,list<int>::iterator> M; // 
        int keep = k;
        unordered_map<int,vector<int>> pos;
        int cnt = 0;
        set<int> S;
        int nidx = -1;
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            pos[a[i]].push_back(i);
            if (M.count(a[i])) {
                auto it = M[a[i]];
                ls.erase(it);
                ls.push_back(i);
                M[a[i]] = prev(ls.end());
                if (int(pos[a[i]].size()) - 1 - m >= 0) {
                    S.erase(pos[a[i]][pos[a[i]].size() - 1 - m]);
                }
                if (int(pos[a[i]].size()) >= m) {
                    S.insert(pos[a[i]][pos[a[i]].size() - m]);
                }
            } else {
                ls.push_back(i);
                M[a[i]] = prev(ls.end());
                if (int(pos[a[i]].size()) >= m) {
                    S.insert(pos[a[i]][pos[a[i]].size() - m]);
                }
            }

            if (int(ls.size()) > keep) {
                auto it = ls.begin();
                int idx = *it;
                ls.pop_front();
                M.erase(a[idx]);
                nidx = idx;
                if (int(pos[a[idx]].size()) >= m) {
                    S.erase(pos[a[idx]][pos[a[idx]].size() - m]);
                }
            }

            if (int(S.size()) >= keep) {
                ans += max(0, *S.begin() - nidx);
            }
        }
        return ans;
    }
};