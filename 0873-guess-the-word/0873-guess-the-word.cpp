/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */
class Solution {
public:
    unordered_map<string,unordered_map<int,vector<string>>> g;
    unordered_set<string> allowed;
    int findMatching(string &s, string &t) {
        int cnt = 0;
        for (int i = 0; i < s.size(); i++) if (s[i] == t[i]) cnt++;
        return cnt;
    }
    void dfs(string& u, Master& master) {
        int cnt = master.guess(u);
        allowed.erase(u);
        unordered_set<string> nallowed;
        for (auto &v : g[u][cnt]) if (allowed.count(v)) nallowed.insert(v);
        allowed = nallowed;
        for (auto v : nallowed) if (allowed.count(v)) dfs(v, master);
    }
    void findSecretWord(vector<string>& words, Master& master) {
        int n = words.size();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < i; j++) {
                int cnt = findMatching(words[i], words[j]);
                g[words[i]][cnt].push_back(words[j]);
                g[words[j]][cnt].push_back(words[i]);
            }
        for (auto &[u, M] : g)
            for (auto &[cnt, list] : M)
                random_shuffle(list.begin(), list.end());
        for (auto &w : words) allowed.insert(w);
        dfs(words[0], master);
    }
};