#define N 8
int buf[100000], top = 0;
int b[100000], top2 = 0;
void add(vector<int> &v) {
    top2 = 0;
    for (int i = 0; i < v.size(); i++) 
        for (int j = 0; j < v[i]; j++) b[top2++] = v[i];
    int SZ = 1;
    for (int j = 1; j <= top2; j++) SZ *= j;
    for (int cnt = 0; cnt < SZ; cnt++) {
        int cur = 0;
        for (int j = 0; j < top2; j++) cur = 10 * cur + b[j];
        buf[top++] = cur;
        next_permutation(b, b + top2);
    }
}
void dfs(int i, int len, vector<int> &path) {
    if (i == N) {
        add(path);
        return;
    }

    dfs(i + 1, len, path);
    if (i + len < N) {
        path.push_back(i);
        dfs(i + 1, len + i, path);
        path.pop_back();
    }
}
auto init = [] {
    vector<int> path;
    dfs(1, 0, path);
    sort(buf, buf + top);
    top = unique(buf, buf + top) - buf;
    return 0;
}();
class Solution {
public:
    int nextBeautifulNumber(int n) {
        int idx = upper_bound(buf, buf + top, n) - buf;
        return buf[idx];
    }
};