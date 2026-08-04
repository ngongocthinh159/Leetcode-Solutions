class Solution {
public:
    vector<int> countTasks(vector<int>& tasks, vector<int>& shifts) {
        int j = 0;
        int m = tasks.size();
        int n = shifts.size();
        long long time = 0;
        long long taskTime = tasks[0];
        vector<long long> pref(m + 1);
        for (int i = 0; i < m; i++) pref[i + 1] = pref[i] + tasks[i];
        vector<int> res(n);
        for (int i = 0; i < n; i++) {
            time += shifts[i];
            long long take = min(time, taskTime);
            taskTime -= take;
            time -= take;

            if (taskTime == 0) {
                j++;
                if (j != m) {
                    int l = j - 1, r = m;
                    while (r - l > 1) {
                        int mid = l + (r - l)/2;
                        if (pref[mid + 1] - pref[j] <= time) 
                            l = mid;
                        else
                            r = mid;
                    }
                    time -= pref[l + 1] - pref[j];
                    j = l + 1;
                    if (j < m)
                        taskTime = tasks[j];
                }
            }
    
            res[i] = m - j;

            if (j == m) {
                j = 0;
                taskTime = tasks[0];
                time = 0;
            }
        }
        return res;
    }
};