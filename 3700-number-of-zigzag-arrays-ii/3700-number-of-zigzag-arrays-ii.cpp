#define ll long long
const int MOD = 1e9 + 7;
struct Matrix {
    vector<vector<ll>> a;
    int n, m;
    Matrix(int _n, int _m) : n(_n), m(_m) {
        a.assign(n, vector<ll>(m, 0));
    }
    Matrix(vector<vector<ll>> &v) {
        n = v.size();
        m = v[0].size();
        a.assign(n, vector<ll>(m, 0));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) 
                a[i][j] = v[i][j];
    }
    Matrix(const vector<vector<ll>> &v) {
        n = v.size();
        m = v[0].size();
        a.assign(n, vector<ll>(m, 0));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) 
                a[i][j] = v[i][j];
    }

    Matrix operator*(Matrix& b) {
        assert(m == b.n);
        int x = n, y = m, z = b.m;
        Matrix c(x, z);
        for (int i = 0; i < x; i++)
            for (int k = 0; k < y; k++)
                for (int j = 0; j < z; j++) {
                    c[i][j] += a[i][k] * b[k][j];
                    if (c[i][j] >= 1LL*MOD*MOD) c[i][j] -= 1LL * MOD * MOD;
                }
        for (int i = 0; i < x; i++)
            for (int j = 0; j < z; j++)
                c[i][j] %= MOD;
        return c;
    }

    Matrix pow(ll p) {
        assert(n == m);
        Matrix res = Matrix::Identity(n);
        Matrix cur = *this;
        for (; p; p >>= 1, cur = cur * cur) {
            if (p & 1)
                res = res * cur;
        }
        return res;
    }

    static Matrix Identity(int sz) {
        Matrix res(sz, sz);
        for (int i = 0; i < sz; i++)
            res[i][i] = 1;
        return res;
    }

    vector<ll>& operator[](int i) {
        return a[i];
    }
    const vector<ll>& operator[](int i) const {
        return a[i];
    }

    friend ostream& operator<<(ostream& os, Matrix &a) {
        for (int i = 0; i < a.n; i++) {
            for (int j = 0; j < a.m; j++)
                os << a[i][j] << " ";
            os << "\n";
        }
        return os;
    }
};

class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        r -= l; r++;
        int len = 2*r;
        Matrix M(len, len);
        Matrix a(vector<vector<ll>>(len, vector<ll>(1, 1)));
        for (int ndir = 1; ndir >= 0; ndir--) {
            for (int nval = 0; nval < r; nval++) {
                int row = nval + r - ndir * r;
                for (int dir = 0; dir < 2; dir++) {
                    for (int val = 0; val < r; val++) {
                        int col = val + r - dir * r;
                        if (ndir == 1 && dir == 0 && val < nval) M[row][col] = 1;
                        if (ndir == 0 && dir == 1 && val > nval) M[row][col] = 1;
                    }
                }
            }
        }
        M = M.pow(n - 1);
        a = M * a;
        ll ans = 0;
        for (int i = 0; i < len; i++) ans = (ans + a[i][0]) % MOD;
        return ans;
    }
};