#define ll long long
#define B 31
class Solution {
public:
    struct node {
        node* child[2];
        int cnt = 0;
        node() {
            child[0] = child[1] = nullptr;
        }
    };
    void insert(node*root, int x) {
        node*p = root;
        int idx;
        p->cnt++;
        for (int bit = B - 1; bit >= 0; bit--) {
            idx = (x >> bit) & 1;
            if (!p->child[idx])  p->child[idx] = new node;
            p = p->child[idx];
            p->cnt++;
        }
    }
    ll get_ans(node* root, int x, int high) {
        node*p = root;
        ll ans = 0;
        int cbit, idx, idx0, idx1;
        for (int bit = B - 1; bit >= 0; bit--) {
            cbit = (high >> bit) & 1;
            idx = (x >> bit) & 1;
            idx0 = idx;
            idx1 = idx^1;
            if (cbit) {
                if (p->child[idx0]) ans += p->child[idx0]->cnt;
                if (p->child[idx1]) p = p->child[idx1];
                else break;
            } else {
                if (p->child[idx0]) p = p->child[idx0];
                else break;
            }
            if (bit == 0) ans += p->cnt;
        }
        return ans;
    }
    ll cal(vector<int>& nums, int high) {
        int n = nums.size();
        node* root = new node;
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            ans += get_ans(root, nums[i], high); 
            insert(root, nums[i]);
        }
        return ans;
    }
    int countPairs(vector<int>& nums, int low, int high) {
        return cal(nums, high) - cal(nums, low - 1);
    }
};