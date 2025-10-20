class Solution {
public:
    int finalValueAfterOperations(vector<string>& operations) {
        int x = 0;
        for (auto &op : operations) {
            if (op.contains('+')) x++;
            else x--;
        }
        return x;
    }
};