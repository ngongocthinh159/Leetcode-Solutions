class Solution {
public:
    long long kthSmallestProduct(vector<int>& nums1, vector<int>& nums2, long long k) {
        auto count = [&](long long x) -> long long { // a * b <= x
            long long res = 0;
            int n = nums1.size(), m = nums2.size();
            int idx1 = n, idx2 = m;
            for (int i = n - 1; i >= 0; i--) if (nums1[i] >= 0) idx1 = i;
            for (int i = m - 1; i >= 0; i--) if (nums2[i] >= 0) idx2 = i;
            if (x >= 0) {
                res += 1LL * idx1 * (m - idx2);
                res += 1LL * (n - idx1) * idx2;
                for (int i = idx1 - 1, j = 0; i >= 0; i--) {
                    while (j < idx2 && 1ll * nums1[i] * nums2[j] > x) j++;
                    res += idx2 - j;
                }
                for (int i = idx1, j = m - 1; i < n; i++) {
                    while (j >= idx2 && 1ll * nums1[i] * nums2[j] > x) j--;
                    res += (j - idx2 + 1);
                }
            } else {
                for (int i = 0, j = idx2; i < idx1; i++) {
                    while (j < m && 1ll * nums1[i] * nums2[j] > x) j++;
                    res += (m - j);
                }
                for (int i = n - 1, j = idx2 - 1; i >= 0; i--) {
                    while (j >= 0 && 1ll * nums1[i] * nums2[j] > x) j--;
                    res += j + 1;
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