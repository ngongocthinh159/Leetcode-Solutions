class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        vector<int> v;
        for (int len = 2; len <= 9; len++) {
            for (int i = 1; i + len - 1 <= 9; i++) {
                int cur = 0;
                for (int j = i; j < i + len; j++) {
                    cur = 10*cur + j;      
                }
                v.push_back(cur);  
            }
            
        }
        vector<int> res;
        for (auto num : v) {
            if (low <= num && num <= high) res.push_back(num);
        }
        return res;
    }
};