#define gcd __gcd
struct ds {
    vector<pair<int,int>> front;
    vector<pair<int,int>> back;
    ds() {}
    void push(int x) {
        if (!back.size()) {
            back.push_back({x, x});
        } else {
            back.push_back({x, gcd(x, back.back().second)});
        }
    }
    void pop() {
        if (!front.size()) {
            while (back.size()) {
                if (!front.size())
                    front.push_back({back.back().first, back.back().first});
                else
                    front.push_back({back.back().first, gcd(back.back().first, front.back().second)});
                back.pop_back();
            }
        }
        if (front.size()) 
            front.pop_back();
    }
    int cur() {
        int x = -1;
        if (back.size()) x = back.back().second;
        if (front.size()) {
            if (x == -1) x = front.back().second;
            else x = gcd(x, front.back().second);
        }
        return x;
    }
};
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size(), IINF = 1e9;
        int o = 0;
        for (auto x : nums) if (x == 1) o++;
        if (o) return n - o;

        ds q;
        int mn = IINF; 
        for (int r = 0, l = 0; r < n; r++) {
            q.push(nums[r]);
            while (l <= r && q.cur() == 1) {
                mn = min(mn, r - l);
                q.pop();
                l++;
            }
            // cout << l << ' ' << r << '\n';
        }
        // cout << mn << '\n';
        if (mn == IINF) return -1;
        return mn + n - 1;
    }
};