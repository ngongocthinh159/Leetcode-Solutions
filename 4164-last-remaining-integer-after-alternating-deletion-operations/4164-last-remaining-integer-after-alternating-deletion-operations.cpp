#define ll long long
class Solution {
public:
    ll dfs(ll s, ll e, ll dif, int dir) {
        ll len = (e - s) / dif + 1;
        if (len == 1) return s;

        ll ns, ne, ndif = dif * 2, ndir = -dir;
        if (dir == 1) {
            ns = s;
            ne = (len&1) ? e : e - dif;
        } else {
            ns = (len&1) ? s : s + dif;
            ne = e;
        }
        return dfs(ns, ne, ndif, ndir);
    }
    long long lastInteger(long long n) {
        return dfs(1, n, 1, 1);    
    }
};