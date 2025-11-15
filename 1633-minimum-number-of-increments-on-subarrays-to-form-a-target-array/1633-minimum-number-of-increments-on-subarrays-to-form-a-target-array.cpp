class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        int n = target.size(), ans = 0;
        int prev = 0;
        for (int i = 0; i  <n ; i++) {
            ans += max(0, target[i] - prev);
            prev = target[i];
        }
        return ans;
    }
};