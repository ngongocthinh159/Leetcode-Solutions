class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        vector<int> matchSuffixIdx(m, -1);
        {
            int j = n - 1;
            for (int i = m - 1; i >= 0; i--) {
                char c = word2[i];
                while (j >= 0 && word1[j] != c) j--;
                if (j >= 0) {
                    matchSuffixIdx[i] = j;
                    j--;
                }
            }
        }
        vector<bool> vis(m);
        vector<int> res;
        int j = 0;
        for (int i = 0; i < m; i++) {
            bool found = true;
            if (i - 1 >= 0 && !vis[i - 1]) {
                char c = word2[i - 1];
                while (j < n && word1[j] != c) j++;
                if (j == n) found = false;
                else {
                    vis[i - 1] = 1;
                    res.push_back(j);
                    j++;
                }
            }
            
            if (!found) break;

            if (word2[i] == word1[j]) {
                vis[i] = 1;
                res.push_back(j);
                j++;
                continue;
            }

            if (j < n) {
                bool match;
                if (i + 1 >= m) match = true;
                else {
                    match = matchSuffixIdx[i + 1] >= j + 1;
                }
                if (match) {
                    res.push_back(j);
                    for (int ii = i + 1, jj = j + 1; ii < m; ii++) {
                        char c = word2[ii];
                        while (jj < n && word1[jj] != c) jj++;
                        res.push_back(jj);
                        jj++;
                    }

                    return res;
                }
            }
        }
        if (res.size() == m) return res;
        return {};
    }
};