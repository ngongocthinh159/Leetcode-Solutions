class Solution {
public:
    int closestTarget(vector<string>& words, string target, int startIndex) {
        int n = words.size();
        int mn = INT_MAX;
        for (int i = 0; i < n; i ++) if (words[i] == target) mn = min(mn, min(abs(i - startIndex), n - abs(i - startIndex)));
        return mn == INT_MAX ? -1 : mn;
    }
};