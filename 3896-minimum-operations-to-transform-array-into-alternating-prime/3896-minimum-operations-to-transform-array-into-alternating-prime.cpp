#define N 200005
bitset<N> isPrime;
vector<int> primes;
auto init = []{
    isPrime.flip();
    isPrime[0] = isPrime[1] = 0;
    for (int i = 2; i * i < N; i++) if (isPrime[i])
        for (int j = i * i; j < N; j += i) isPrime[j] = 0;
    for (int i = 0; i < N; i++) if (isPrime[i]) primes.push_back(i);
    return 0;
}();
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (i & 1) {
                while (isPrime[nums[i]]) ans++, nums[i]++;
            } else {
                if (!isPrime[nums[i]]) {
                    auto it = upper_bound(primes.begin(), primes.end(), nums[i]);
                    ans += *it - nums[i];
                }
            }
        }
        return ans;
    }
};