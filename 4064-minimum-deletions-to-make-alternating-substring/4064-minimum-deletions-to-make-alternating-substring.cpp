#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key


class Solution {
public:
    vector<int> minDeletions(string s, vector<vector<int>>& queries) {
        int n = s.size(), q = queries.size();
        pbds S;

        for (int i = 0; i < n;) {
            char c = s[i];
            int st = i, end = i;
            while (i < n && s[i] == c) end = i++;
            S.insert({st, end});
        }

        vector<int> ans;
        auto find = [&](int idx) -> pbds::iterator {
            auto it = S.upper_bound({idx, INT_MAX});
            it--;
            return it;
        };

        int t, j, l, r;
        for (int i = 0; i < q; i++) {
            t = queries[i][0];
            if (t == 1) {
                j = queries[i][1];

                auto it = find(j);
                auto [ll, rr] = *it;
                if (ll == j && rr == j) {
                    int st = j, end = j;
                    if (j - 1 >= 0) {
                        // auto pit = prev(it);
                        auto pit = find(j - 1);
                        st = (*pit).first;
                        S.erase(pit);
                    }
                    if (j + 1 < n) {
                        // auto nit = next(it);
                        auto nit = find(j + 1);
                        end = (*nit).second;
                        S.erase(nit);
                    }
                    S.erase(it);
                    S.insert({st, end});
                } else if (ll == j) {
                    int st = j, end = j;
                    if (j - 1 >= 0) {
                        // auto pit = prev(it);
                        auto pit = find(j - 1);
                        st = (*pit).first;
                        S.erase(pit);
                    }
                    S.erase(it);
                    S.insert({st, end});
                    S.insert({j + 1, rr});
                } else if (rr == j) {
                    int st = j, end = j;
                    if (j + 1 < n) {
                        // auto nit = next(it);
                        auto nit = find(j + 1);
                        end = (*nit).second;
                        S.erase(nit);
                    }
                    S.erase(it);
                    S.insert({st, end});
                    S.insert({ll, j - 1});
                } else {
                    S.erase(it);
                    S.insert({j, j});
                    S.insert({ll, j - 1});
                    S.insert({j + 1, rr});
                }

                // s[j] ^= 'A' ^ 'B';
            } else if (t == 2) {
                l = queries[i][1], r = queries[i][2];
                // int res = 0;
                auto it1 = S.upper_bound({l, INT_MAX});
                it1--;
                // cout << (*it1).first << " " << (*it1).second << "\n";

                auto it2 = S.upper_bound({r, INT_MAX});
                it2--;
                // cout << (*it2).first << " " << (*it2).second << "\n";
                // for (auto p : S) {
                //     cout << p.first << " " << p.second << "\n"; 
                // }
                // cout << "\n";
                // cout << "\n";
                int res = S.order_of_key(*it2) - S.order_of_key(*it1) + 1;
                ans.push_back(r - l + 1 - res);
            }
        }
        return ans;
    }
};