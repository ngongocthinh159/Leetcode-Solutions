struct query {
    int l, r, idx;
};
struct _data {
    unordered_map<int,int> f;
    int odd;
    bool isGood(int k) {
        return odd == 0 && (int(f.size()) == k);
    }
};
class Solution {
public:
    vector<bool> validSubarrays(vector<int>& nums, int K, vector<vector<int>>& queries) {
        int n = nums.size();
        int blockSize = sqrt(n);
        int m = queries.size();
        vector<query> qs(m);
        for (int i = 0; i < m; i++) qs[i].l = queries[i][0], qs[i].r = queries[i][1], qs[i].idx = i;
        int numBlock = (n + blockSize - 1) / blockSize;
        vector<vector<query>> blocks(numBlock);
        for (int i = 0; i < m; i++) {
            int blockNum = qs[i].l / blockSize;
            blocks[blockNum].push_back(qs[i]);
        }
        for (auto &list : blocks) {
            sort(list.begin(), list.end(), [](auto &a, auto &b) {
                return a.r < b.r;
            });
        }
        auto add = [&](int x, _data &myData) {
            if (myData.f[x] & 1) myData.odd--;
            else myData.odd++;
            myData.f[x]++;
        };
        auto remove = [&](int x, _data &myData) {
            if (myData.f[x] & 1) myData.odd--;
            else myData.odd++;
            myData.f[x]--;
            if (myData.f[x] == 0) myData.f.erase(x);
        };
        vector<bool> ans(m);
        for (int i = 0; i < numBlock; i++) {
            auto &list = blocks[i];
            if (!list.size()) continue;
            _data myData{};
            for (int j = list[0].l; j <= list[0].r; j++) {
                add(nums[j], myData);
            }
            ans[list[0].idx] = myData.isGood(K);

            for (int k = 1; k < int(list.size()); k++) {

                for (int j = list[k - 1].r + 1; j <= list[k].r; j++) add(nums[j], myData);
                if (list[k - 1].l <= list[k].l) {
                    for (int j = list[k - 1].l; j < list[k].l; j++) remove(nums[j], myData);
                } else {
                    for (int j = list[k - 1].l - 1; j >= list[k].l; j--) add(nums[j], myData);
                }

                ans[list[k].idx] = myData.isGood(K);
            }
        }
        return ans;
    }
};