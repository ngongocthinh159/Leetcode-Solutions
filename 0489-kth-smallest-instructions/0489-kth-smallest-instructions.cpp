#define N 32
int C[N][N];
auto init = [] {
    for (int i = 0; i < N; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
    return 0;
}();
class Solution {
public:
    string kthSmallestPath(vector<int>& destination, int k) {
        int H = destination[1], V = destination[0];
        int tot = H + V;
        string res = "";
        for (int i = 0; i < tot; i++) {
            if (H==0) res += "V";
            else if (V==0) res += "H";
            else {
                H--;
                if (C[H + V][H] >= k) {
                    res += "H";
                } else {
                    k -= C[H + V][H];
                    H++;
                    V--;
                    res += "V"; 
                }
            }
        }
        return res;
    }
};