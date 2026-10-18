struct Node {
    int val;
    Node* left;
    Node* right;    
    Node(int x) {
        val = x;
        left = right = nullptr;
    }
};
#define N 1005
const int MOD = 1e9 + 7;
int fact[N], inv[N];
int expo(int a, int b) {
    int res = 1;
    int cur = a;
    while (b) {
        if (b & 1) res = 1ll * res * cur % MOD;
        cur = 1ll * cur * cur % MOD;
        b >>= 1;
    }
    return res;
}
auto init = []{
    fact[0] = 1;
    for (int i = 1; i < N; i++) fact[i] = 1ll * fact[i - 1] * i % MOD; 
    inv[N - 1] = expo(fact[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; i--) inv[i] = 1ll * inv[i + 1] * (i + 1) % MOD;
    return 0;
}();
class Solution {
public:
    void insert(Node* root, int x) {
        Node* p = root;
        Node* pp = root;
        while (p) {
            pp = p;
            if (x < p->val)  p = p->left;
            else p = p->right;
        }
        if (x < pp->val) pp->left = new Node(x);
        if (x > pp->val) pp->right = new Node(x);
    }
    int nCk(int n, int k) {
        if (k > n) return 0;
        return 1ll * fact[n] * inv[n - k] % MOD * inv[k] % MOD;
    }
    pair<int,int> dfs(Node* root) {
        if (!root) return {1, 0};
        auto [resL, cntL] = dfs(root->left);
        auto [resR, cntR] = dfs(root->right);
        return {1ll * resL * resR % MOD * nCk(cntL + cntR, cntL) % MOD, cntL + cntR + 1};
    }
    int numOfWays(vector<int>& nums) {
        int n = nums.size();
        Node* root = new Node(nums[0]);
        for (int i = 1; i < n; i++) insert(root, nums[i]);
        return ((dfs(root).first - 1) % MOD + MOD) % MOD;
    }
};