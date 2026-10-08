struct DS {
    vector<long long> suf;
    vector<long long> pref;
    vector<long long> a;
    vector<long long> p;
    const int MOD = 1e9 + 7;
    int n;
    DS(vector<int> &arr) {
        n = arr.size();
        suf.resize(n);
        pref.resize(n);
        a.resize(n);
        p.resize(n);
        build(arr);
    }
    void build(vector<int> &arr) {
        suf[0] = arr[0];
        a[0] = arr[0];
        p[0] = arr[0];
        for (int i = 1; i < n; i++) {
            p[i] = (p[i - 1] + arr[i]) % MOD;
            suf[i] = (suf[i - 1] + 1ll * (i + 1) * arr[i] % MOD) % MOD; 
            a[i] = (a[i - 1] + suf[i]) % MOD;
        }
        pref[n - 1] = arr[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            pref[i] = (pref[i + 1] + 1ll * (n - i) * arr[i] % MOD) % MOD;
        }
    }
    long long queryPref(int l, int r) {
        long long res = pref[l] - (r == n - 1 ? 0 : pref[r + 1]) % MOD;
        if (res < 0) res += MOD;
        long long tmp = (p[r] - (l == 0 ? 0 : p[l - 1])) % MOD;
        if (tmp < 0) tmp += MOD;
        res -= (n - r - 1) * tmp % MOD;
        res %= MOD;
        if (res < 0) res += MOD;
        return res;
    }
    long long query(int l, int r) {
        long long res = (a[r] - (l == 0 ? 0 : a[l - 1])) % MOD;
        if (res < 0) res += MOD;
        if (l - 1 >= 0) {
            res -= suf[l - 1] * (r - l + 1) % MOD;
            res %= MOD;
            if (res < 0) res += MOD;

            res -= queryPref(l, r) * l % MOD;
            res %= MOD;
            if (res < 0) res += MOD;
        }
        return res;
    }
};
class Solution {
public:
    int totalStrength(vector<int>& strength) {
        int n = strength.size();
        DS ds(strength);
        vector<int> st;
        vector<int> R(n), L(n);
        for (int i = n - 1; i >= 0; i--) {
            while (st.size() && strength[i] < strength[st.back()]) {
                L[st.back()] = i + 1;
                st.pop_back();
            }
            R[i] = st.empty() ? n - 1 : st.back() - 1;
            st.push_back(i);
        }
        while (st.size()) {
            L[st.back()] = 0;
            st.pop_back();
        }
        const int MOD = 1e9 + 7;
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            long long tmp = ds.query(L[i], R[i]);
            if (i - 1 >= L[i]) {
                tmp -= ds.query(L[i], i - 1);
                tmp %= MOD;
                if (tmp < 0) tmp += MOD;
            }
            if (i + 1 <= R[i]) {
                tmp -= ds.query(i + 1, R[i]);
                tmp %= MOD;
                if (tmp < 0) tmp += MOD;
            }

            ans += strength[i] * tmp % MOD;
            ans %= MOD;
        }
        return ans;
    }
};