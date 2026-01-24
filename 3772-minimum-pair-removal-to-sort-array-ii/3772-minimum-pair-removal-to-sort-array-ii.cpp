#define N 100005
#define ll long long
#define prev __prev
#define next __next
int prev[N], next[N];
class Solution {
public:
    int minimumPairRemoval(vector<int>& arr) {
        vector<ll> nums(arr.begin(), arr.end());
        int n = arr.size(), cnt = 0, ans = 0;
        priority_queue<array<ll, 3>,vector<array<ll, 3>>, greater<>> q;
        vector<bool> removed(n);
        for (int i = 0; i < n; i++) {   
            prev[i] = i - 1;
            next[i] = i + 1; 
            if (i > 0) {
                q.push({nums[i] + nums[i - 1], i - 1, i});
                if (nums[i] < nums[i - 1]) cnt++;
            }
        }
        while (q.size() && cnt) {
            auto [sum, l, r] = q.top();
            q.pop();
            if (removed[l] || removed[r] || nums[l] + nums[r] != sum) continue;
            // cout << l << ' ' << r << '\n';
            ans++;

            if (nums[l] > nums[r]) cnt--;
            if (prev[l] != -1) {
                if (nums[prev[l]] > nums[l]) cnt--;
                if (nums[prev[l]] > sum) cnt++;
                q.push({nums[prev[l]] + sum, prev[l], l});
            }
            if (next[r] != n) {
                if (nums[r] > nums[next[r]]) cnt--;
                if (sum > nums[next[r]]) cnt++;
                q.push({sum + nums[next[r]], l, next[r]});
                prev[next[r]] = l;
            }

            nums[l] = sum;
            next[l] = next[r];
            removed[r] = 1;
        }
        return ans;
    }
};