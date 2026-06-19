class Solution {
    string candidates = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int LEN = 6;
    unordered_map<string,string> toOriginal;
    string prefix = "http://tinyurl.com/";
    int getRand(int l, int r) {
        return l + rand() % (r - l + 1);
    }
    string getRandomKey() {
        string t = "";
        for (int i = 0; i < LEN; i++) {
            t += candidates[getRand(0, candidates.size() - 1)];
        }
        return t;
    }
public:
    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        string key;
        while (1) {
            key = getRandomKey();
            if (!toOriginal.count(key)) break;
        }
        toOriginal[key] = longUrl;
        return prefix + key;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        return toOriginal[shortUrl.substr(int(prefix.size()))];
    }
};


// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));