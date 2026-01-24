#define N 100005
#define ll long long
#define prev __prev
#define next __next
int prev[N], next[N];
class Solution {
public:
    int minimumPairRemoval(vector<int>& arr) {
        vector<ll> nums(arr.begin(), arr.end());
        int n = nums.size(), cnt = 0, ans = 0;
        priority_queue<array<ll, 5>,vector<array<ll, 5>>, greater<>> q;
        vector<int> len(n, 1);
        vector<bool> removed(n);
        for (int i = 0; i < n; i++) {   
            prev[i] = i - 1;
            next[i] = i + 1; 
            if (i > 0) {
                q.push({nums[i] + nums[i - 1], i - 1, 1, i, 1});
                if (nums[i] < nums[i - 1]) cnt++;
            }
        }
        while (q.size() && cnt) {
            auto [sum, l, lenl, r, lenr] = q.top();
            q.pop();
            // lazy deletion: a pair is staled either the len of left segment or len of right segment does not follow the latest len
            if (len[l] != lenl || len[r] != lenr) continue;
            ans++;

            if (nums[l] > nums[r]) cnt--;
            if (prev[l] != -1) {
                if (nums[prev[l]] > nums[l]) cnt--;
                if (nums[prev[l]] > sum) cnt++;
                q.push({nums[prev[l]] + sum, prev[l], len[prev[l]], l, len[l] + len[r]});
            }
            if (next[r] != n) {
                if (nums[r] > nums[next[r]]) cnt--;
                if (sum > nums[next[r]]) cnt++;
                q.push({sum + nums[next[r]], l, len[l] + len[r], next[r], len[next[r]]});
                prev[next[r]] = l;
            }

            nums[l] = sum;
            next[l] = next[r];
            len[l] += len[r];
            len[r] = len[l];
        }
        return ans;
    }
};