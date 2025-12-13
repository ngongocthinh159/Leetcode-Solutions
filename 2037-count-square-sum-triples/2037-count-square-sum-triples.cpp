class Solution {
public:
    int countTriples(int n) {
        int ans = 0;
        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++) {
                long long k = i*i + j*j;
                long long tmp = sqrt(k);
                if (tmp <= n && tmp * tmp == k) ans+=2;
            }
        return ans;
    }
};