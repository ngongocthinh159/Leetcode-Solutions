struct query {
    int l, r, idx, th;
};
class Solution {
public:
    vector<int> subarrayMajority(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(), m = queries.size();
        const int BLOCK_SIZE = sqrt(n);

        vector<set<int>> f(n + 1);
        unordered_map<int,int> curf;
        curf.reserve(n);
        int mxf = 0;

        vector<query> qs(m);
        for (int i = 0; i < m; i++) {
            qs[i].l = queries[i][0];
            qs[i].r = queries[i][1];
            qs[i].idx = i;
            qs[i].th = queries[i][2];
        }
        sort(qs.begin(), qs.end(), [&](const auto &q1, const auto &q2) {
            int b1 = q1.l / BLOCK_SIZE;
            int b2 = q2.l / BLOCK_SIZE;
            if (b1 < b2) return true;
            if (b1 == b2 && q1.r < q2.r) return true;
            return false;
        });
        auto add = [](int x, vector<set<int>> &f, unordered_map<int,int> &curf, int &mxf) {
            f[curf[x]].erase(x);
            f[++curf[x]].insert(x);
            if (curf[x] > mxf) mxf = curf[x];
        };
        auto remove = [](int x, vector<set<int>> &f, unordered_map<int,int> &curf, int &mxf) {
            f[curf[x]].erase(x);
            if (--curf[x] != 0) f[curf[x]].insert(x);
            if (!f[mxf].size()) mxf--;
        };
        vector<int> ans(m);
        {
            int i = 0;
            int l = 0, r = -1;
            while (i < m) {
                int curBlock = qs[i].l / BLOCK_SIZE;
                while (i < m && qs[i].l / BLOCK_SIZE == curBlock) {
                    while (r < qs[i].r) {
                        add(nums[++r], f, curf, mxf);
                    }
                    while (l < qs[i].l) {
                        remove(nums[l++], f, curf, mxf);
                    }
                    while (l > qs[i].l) {
                        add(nums[--l], f, curf, mxf);
                    }
                    while (r > qs[i].r) {
                        remove(nums[r--], f, curf, mxf);
                    }

                    if (mxf < qs[i].th)
                        ans[qs[i].idx] = -1;
                    else
                        ans[qs[i].idx] = *f[mxf].begin();

                    i++;
                }
            }
        }
        return ans;
    }
};