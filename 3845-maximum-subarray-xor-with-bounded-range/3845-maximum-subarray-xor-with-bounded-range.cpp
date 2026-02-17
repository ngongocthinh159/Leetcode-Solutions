#define BIT 15
struct node {
    node *child[2];
    int cnt;
    node() {
        child[0] = child[1] = nullptr;
        cnt = 0;
    }
};

void add(node *root, int x) {
    node *p = root;
    int idx ;
    p->cnt++;
    for (int i = BIT - 1; i >= 0; i--) {
        idx = (x >> i) & 1;
        if (!p->child[idx]) p->child[idx] = new node;
        p = p->child[idx];
        p->cnt++;
    }
}

void remove(node *root, int x) {
    node *p = root;
    int idx;
    p->cnt--;
    for (int i = BIT - 1; i >= 0; i--) {
        idx = (x >> i) & 1;
        p = p->child[idx];
        p->cnt--;
    }
}

int query(node *root, int x) {
    node *p = root;
    int idx, desired, res = 0;
    for (int i = BIT - 1; i >= 0; i--) {
        idx = ((x >> i) & 1);
        desired = idx ^ 1;
        if (p->child[desired] != nullptr && p->child[desired]->cnt != 0) {
            res = res ^ (1 << i);
            p = p->child[desired];
        } else {
            p = p->child[desired ^ 1];
        }
    }
    return res;
}
class Solution {
public:
    int maxXor(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = 0;
        node *root = new node;
        deque<int> mnq, mxq;
        vector<int> pref(n + 1);
        add(root, 0);
        for (int i = 0, l = 0; i < n; i++) {
            pref[i + 1] = pref[i] ^ nums[i];

            while (mnq.size() && nums[mnq.back()] >= nums[i]) mnq.pop_back();
            mnq.push_back(i);
            while (mnq.size() && !(l <= mnq.front() && mnq.front() <= i)) mnq.pop_front();

            while (mxq.size() && nums[mxq.front()] <= nums[i]) mxq.pop_front();
            mxq.push_front(i);
            while (mxq.size() & !(l <= mxq.back() && mxq.back() <= i)) mxq.pop_back();

            int cmn = nums[mnq.front()];
            int cmx = nums[mxq.back()];
            while (l < i && cmx - cmn > k) {
                remove(root, pref[l]);
                l++;
                while (mnq.size() && !(l <= mnq.front() && mnq.front() <= i)) mnq.pop_front();
                while (mxq.size() && !(l <= mxq.back() && mxq.back() <= i)) mxq.pop_back();
                cmn = nums[mnq.front()];
                cmx = nums[mxq.back()];
            }

            ans = max(ans, query(root, pref[i + 1]));
            add(root, pref[i + 1]);
        }
        return ans;
    }
};