#define ll long long
class Solution {
public:
    vector<int> numberOfPairs(vector<int>& nums1, vector<int>& n2, vector<vector<int>>& queries) {
        int n = nums1.size();
        int m = n2.size();
        vector<ll> nums2(m);
        for (int i = 0; i < m; i++) nums2[i] = n2[i];
        int blockSize = 0;
        while (blockSize*blockSize < m) blockSize++;
        int numBlock = (m + blockSize - 1) / blockSize;
        vector<int> blockStart(numBlock);
        vector<int> blockEnd(numBlock);
        vector<int> blockId(m);
        vector<ll> blockLazy(numBlock);
        vector<unordered_map<ll,ll>> blockMap(numBlock);
        for (int i = 0, j = 0; i < numBlock; i++, j += blockSize) {
            blockStart[i] = j;
            blockEnd[i] = min(j + blockSize - 1, m - 1);
            for (int k = blockStart[i]; k <= blockEnd[i]; k++) {
                blockId[k] = i;
                blockMap[i][nums2[k]]++;
            }
        }
        auto update = [&](int l, int r, int id, ll val) {
            for (int i = l; i <= r; i++) {
                blockMap[id][nums2[i]]--;
                nums2[i] += val;
                blockMap[id][nums2[i]]++;
            }
        };
        vector<int> ans;
        for (auto &q : queries) {
            if (q[0] == 1) {
                int l = q[1], r = q[2];
                ll val = q[3];

                if (blockId[l] == blockId[r]) {
                    update(l, r, blockId[l], val);
                } else {
                    update(l, blockEnd[blockId[l]], blockId[l], val);
                    for (int i = blockId[l] + 1; i <= blockId[r] - 1; i++) {
                        blockLazy[i] += val;
                    }
                    update(blockStart[blockId[r]], r, blockId[r], val);
                }
            } else {
                ll tot = q[1];
                ll cur = 0;
                for (int j = 0; j < n; j++) {
                    ll target = tot - nums1[j];
                    for (int i = 0; i < numBlock; i++) {
                        ll x = target - blockLazy[i];
                        cur += blockMap[i][x];
                    }
                }
                ans.push_back(cur);
            }
        }
        return ans;
    }
};