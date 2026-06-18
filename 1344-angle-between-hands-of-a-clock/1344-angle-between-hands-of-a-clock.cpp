class Solution {
public:
    double angleClock(int hour, int minutes) {
        double deg1;
        if (0 <= minutes && minutes <= 15) {
            deg1 = (15 - minutes) * 6;
        }
        else {
            deg1 = (45 - (minutes - 15)) * 6 + 90;
        }
        if (hour == 12) hour = 0;
        double deg2;
        if (0 <= hour && hour <= 3) {
            deg2 = (3 - hour) * 30;
        } else {
            deg2 = (9 - (hour - 3)) * 30 + 90;
        }
        deg2 -= 1.00 * minutes/60 * 30;
        if (deg2 < 0) deg2 += 360;
        double ans;
        if (deg1 >= deg2) ans = deg1 - deg2;
        else ans = deg2 - deg1;
        if (ans > 180.0) ans = 360.0 - ans;
        // cout << deg1 << ' ' << deg2 << '\n';
        return ans;
    }
};