class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        quickSort(nums, 0, n - 1);
    }
    void quickSort(vector<int> &nums, int left, int right) {
        if (left >= right) return;
        int p = partition(nums, left, right);
        quickSort(nums, left, p - 1);
        quickSort(nums, p + 1, right);
    }
    int partition(vector<int> &nums, int left, int right) {
        int idx = left + random() % (right - left + 1);
        swap(nums[idx], nums[right]);
        int pivot = nums[right];
        int p = left;
        for (int i = left; i < right; i++) {
            if (nums[i] < pivot) {
                swap(nums[p++], nums[i]);
            }
        }
        swap(nums[p], nums[right]);
        return p;
    }
};