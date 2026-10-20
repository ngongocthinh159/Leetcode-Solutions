class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        vector<int> nextDrop(n);
        nextDrop[n - 1] = n;
        for (int i = n - 2; i >= 0; --i) {
            if (nums[i] > nums[i + 1])
                nextDrop[i] = i;
            else
                nextDrop[i] = nextDrop[i + 1];
        }
        int ans = 0;
        for (int len = 1; len <= n; ++len) if (n % len == 0) {
            int prevMx = -1;
            bool okk = true;
            for (int i = 0; i < n; i += len) {
                int end = i + len - 1;
                int mn, mx;
                int cnt = 0;
                bool ok = false;
                if (nextDrop[i] <= end - 1) {
                    cnt++;
                    if (nextDrop[i] + 1 < n && nextDrop[nextDrop[i] + 1] <= end - 1) cnt++;
                }
                if (cnt == 0) {
                    mn = nums[i];
                    mx = nums[end];
                    ok = true;
                } else if (cnt == 1 && nums[i] >= nums[end]) {
                    mn = nums[nextDrop[i] + 1];
                    mx = nums[nextDrop[i]];
                    ok = true;
                }
                ok = ok & (prevMx <= mn);
                if (ok) {
                    prevMx = mx;
                } else {
                    okk = false;
                    break;
                }
            }
            if (okk) {
                ans += len;
            }
        }
        return ans;
    }
};