class Solution {
public:
    long long kthSmallestProduct(vector<int>& nums1, vector<int>& nums2, long long k) {
        auto count = [&](long long x) -> long long { // a * b <= x
            long long res = 0;
            for (auto a : nums1) {
                if (a > 0) {
                    auto idx = upper_bound(nums2.begin(), nums2.end(), floor(1.00 * x / a)) - nums2.begin();
                    res += idx;
                } else if (a < 0) {
                    auto idx = lower_bound(nums2.begin(), nums2.end(), ceil(1.00 * x / a)) - nums2.begin();
                    res += int(nums2.size()) - idx;
                } else {
                    if (x >= 0) res += int(nums2.size());
                }
            }
            return res;
        };
        long long l = -1e15, r = 1e15;
        while (r - l > 1) {
            long long m = l + (r - l)/2;
            if (count(m) >= k) {
                r = m;
            } else {
                l = m;
            }
        }
        return r;
    }
};