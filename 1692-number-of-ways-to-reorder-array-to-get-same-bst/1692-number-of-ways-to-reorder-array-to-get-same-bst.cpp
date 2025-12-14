#define N 100005
#define ll long long
struct node {
    node *left;
    node *right;
    int val;
    node(int _val) : val(_val) {
        left = nullptr;
        right = nullptr;
    }
};
ll fact[N], inv[N];
const int MOD = 1e9 + 7;
ll expo(ll a, ll b) {
    ll res = 1;
    ll cur = a;
    while (b) {
        if (b&1)
            res = res * cur % MOD;
        cur = cur * cur % MOD;
        b >>= 1;
    }
    return res;
}
auto init = [] {
    fact[0] = 1;
    for (int i = 1; i < N; i++) fact[i] = fact[i - 1] * i % MOD;
    inv[N - 1] = expo(fact[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % MOD;
    return 0;
}();
ll nCk(int n, int k) {
    return fact[n] * inv[k] % MOD * inv[n - k] % MOD;
}
class Solution {
public:
    int n;
    node* insert(node *root, int x) {
        if (!root)
            return new node(x);
        if (x > root->val) 
            root->right = insert(root->right, x);
        else 
            root->left = insert(root->left, x);
        return root;
    }
    pair<int,int> dfs(node *root) {
        if (!root) 
            return {0, 1};
        auto lp = dfs(root->left);
        auto rp = dfs(root->right);
        ll ways = 1LL * nCk(lp.first + rp.first, lp.first) * lp.second % MOD * rp.second % MOD;
        return {lp.first + rp.first + 1, ways};
    }
    int numOfWays(vector<int>& nums) {
        n = nums.size();
        node *root = nullptr;
        for (int i = 0; i < n; i++)
            root = insert(root, nums[i]);
        return ((dfs(root).second - 1) % MOD + MOD) % MOD;
    }
};