#define ll long long
struct Node {
    ll sval, eval, slen, elen, tot_mul;
};
struct segtree {
    vector<Node> nodes;
    int n;
    segtree(vector<int>&arr) {
        n = arr.size();
        nodes.resize(4*n);
        build(1, 0, n - 1, arr);
    }
    void build(int idx, int s, int e, vector<int>&arr) {
        if (s == e) {
            nodes[idx] = Node{arr[s], arr[s], 1, 1, 1};
            return;
        }
        int m = (s + e)/2;
        build(2*idx, s, m, arr);
        build(2*idx + 1, m + 1, e, arr);
        nodes[idx] = merge(nodes[2*idx], nodes[2*idx + 1], m - s + 1, e - (m + 1) + 1);
    }
    Node merge(Node &l, Node &r, int lenl, int lenr) {
        Node res;
        if (l.eval > r.sval) {
            res.sval = l.sval;
            res.eval = r.eval;
            res.slen = l.slen;
            res.elen = r.elen;
            res.tot_mul = l.tot_mul + r.tot_mul;
        } else {
            ll len = l.elen + r.slen;
            res.sval = l.sval;
            res.eval = r.eval;
            
            if (l.elen == lenl) 
                res.slen = l.elen + r.slen;
            else 
                res.slen = l.slen;
            
            if (r.slen == lenr)
                res.elen = r.slen + l.elen;
            else
                res.elen = r.elen;
            
            res.tot_mul = l.tot_mul + \
                r.tot_mul - l.elen * (l.elen + 1) / 2 - r.slen * (r.slen + 1) / 2 + len * (len + 1) / 2;
        }
        return res;
    }
    Node query(int idx, int s, int e, int l, int r) {
        if (s > r || l > e || s > e || l > r) return Node{-1,-1,-1,-1,-1};
        if (l <= s && e <= r) return nodes[idx];
        int m = (s + e)/2;
        auto lans = query(2*idx, s, m, l, r);
        auto rans = query(2*idx + 1, m + 1, e, l, r);
        if (lans.sval == -1) {
            return rans;
        } else if (rans.sval == -1)  {
            return lans;
        } else
            return merge(lans, rans, m - s + 1, e - (m + 1) + 1);
    }
};
class Solution {
public:
    vector<long long> countStableSubarrays(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(), q = queries.size();
        segtree tree(nums);
        vector<long long> ans(q);
        for (int i = 0; i < q; i++) {
            int l = queries[i][0], r = queries[i][1];
            ans[i] = tree.query(1, 0, n - 1, l, r).tot_mul;
        }
        return ans;
    }
};