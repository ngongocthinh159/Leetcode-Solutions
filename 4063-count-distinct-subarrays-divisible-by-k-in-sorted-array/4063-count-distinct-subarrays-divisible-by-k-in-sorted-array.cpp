class Solution {
public:
    long long numGoodSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int,long long> f;
        int s = 0, s1 = 0;
        long long ans = 0;
        int j = -1;
        for (int i = 0; i < n;) {
            int st = i, end = i;

            for (; j < st - 1; j++) {
                if (j == -1) f[0]++;
                else {
                    s += nums[j];
                    s %= k;
                    f[s]++;
                }
            }

        
            long long x = nums[i];
            while (i < n && x == nums[i]) {
                s1 += nums[i];
                s1 %= k;
                ans += f[s1];
                end = i;
                i++;
            }
        }
        for (int i = 0; i < n; ){
            int x = nums[i], cnt = 0;
            while (i < n && x == nums[i]) {
                cnt++, i++;
            }
            int g = gcd(x, k);
            int need = k / g;
            int will = cnt / need;
            ans+=will;
        }
        return ans;
    }
};