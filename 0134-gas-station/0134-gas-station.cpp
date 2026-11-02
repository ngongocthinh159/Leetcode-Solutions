class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        vector<int> v(2*n);
        for (int i = 0; i < 2 * n; i++) v[i] = gas[i%n] - cost[i%n];
        for (int i = 0; i < n; ) {
            int start = i;
            int sum = 0;
            int len = 0;
            while (len < n && sum + v[i] >= 0) {
                sum += v[i];
                len++;
                i++;
            }
            if (len == n) return start;
            i = i + 1;
        }
        return -1;
    }
};