#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<pair<long long, int>, null_type, less<pair<long long, int>>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key


class Solution {
public:
    long long countRatioSubarrays(vector<int>& nums, int a, int b) {
        // b * even - a * odd
        // f1 = b * e1 - a * o1
        // f2 = b * e2 - a * o2
        // f2 - f1 = b * (e2 - e1) - a * (o1 - o2) = b * even - a * odd <= 0
        // f2 <= f1
        int n = nums.size();
        long long o = 0, e = 0;
        pbds p;
        int id = 0;
        long long ans = 0;
        int j = -1;
        vector<long long> val(n);
        for (int i = 0; i < n; i++) {
            if (nums[i] & 1) o++;
            else e++;
            val[i] = b * e - a * o;
            
            if (nums[i] & 1) {
                if (j == -1) {
                    p.insert({0, id++});
                    j++;
                }
                while (j < i) p.insert({val[j], id++}), j++;
            }

            auto it = p.lower_bound({val[i], -1});
            if (it != p.end())
                ans += int(p.size()) - p.order_of_key(*it);
        }
        return ans;
    }
};