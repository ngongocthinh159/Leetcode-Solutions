struct MexDS {
    unordered_map<int,int> f;
    int mex;
    MexDS() {
        mex = 0;
    }
    void insert(int x) {
        f[x]++;
        while (f[mex] != 0) mex++;
    }
    void remove(int x) {
        f[x]--;
        if (f[x] == 0 && x <= mex - 1) mex = x;
    }
    int queryMex() {
        return mex;
    }
};
class Solution {
public:
    vector<int> maximumMEX(vector<int>& nums) {
        int n = nums.size();
        MexDS a;
        for (int i = 0; i < n; i++) a.insert(nums[i]);
        vector<int> res;
        int j = 0;
        while (j < n) {
            int mex = a.queryMex();
            MexDS b;
            b.insert(nums[j]);
            int start = j, end = j;
            j++;
            while (j < n && b.queryMex() != mex) {
                b.insert(nums[j]);
                end = j;
                j++;
            }
            // cout << "here" << '\n';
            res.push_back(mex);
            for (int k = start; k <= end; k++) a.remove(nums[k]);
        }
        return res;
    }
};