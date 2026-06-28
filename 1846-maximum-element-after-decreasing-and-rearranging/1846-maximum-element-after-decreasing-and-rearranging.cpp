class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        vector<int> cnt(arr.size() + 1, 0);
        for (int i = 0; i < arr.size(); i++) {
            cnt[min(arr[i], (int) arr.size())]++;
        }
        int i = 1;
        for (int j = 1; j < cnt.size();) {
            if (cnt[j] != 0) {
                if (j >= i) {i++;}
                cnt[j]--;
            } else j++;
        }
        return i - 1;
    }
};